module;
#include <cstddef>
#include <string>
#include <string_view>
#include <memory>
#include <tuple>
#include <unordered_map>
export module Natsuki.Resource.ResourceManager;
import Natsuki.Resource.Concept;
import Natsuki.Utils.TransparentHash;
import Natsuki.Exception;

inline void ResourceError(std::string_view path, std::string func) {
	throw Natsuki::Exception("failed to " + func + " resource at path \"" + std::string(path) + '"');
}

export namespace Natsuki {
	template<class T>
	class ResourceManager {
	private:
		std::unordered_map<std::string, std::shared_ptr<T>
			, transparentHash, transparentEqual> hotCache;
		std::unordered_map<std::string, std::weak_ptr<T>
			, transparentHash, transparentEqual> coldCache;
		static constexpr size_t HOT_MAX_SIZE = 128;

		template<typename ...Args>
			requires ResourceCheck<T, Args...>
		inline bool loadLogic(std::shared_ptr<T> resource, std::string_view path, Args&&...args) {			
			if (!resource->load(path, std::forward<Args>(args)...))
				return false;
			hotCache.emplace(path, resource);
			return true;
		}

		void moveToHot(auto it) {
			hotCache.emplace(it->first, it->second);
			coldCache.erase(it);
		}

	public:
		inline ResourceManager() {
			hotCache.reserve(HOT_MAX_SIZE);
		}
		~ResourceManager() = default;

		template<typename ...Args>
			requires ResourceCheck<T, Args...>
		bool load(std::string_view path, Args&&...args) {
			if (auto it = hotCache.find(path); it != hotCache.end()) {
				return true;
			}
			if (auto it = coldCache.find(path); it != coldCache.end()) {
				if (it->second.expired()) {
					coldCache.erase(it);
				}
				else {
					moveToHot(it);
					return true;
				}
			}
			auto resource = std::make_shared<T>();
			return loadLogic(resource, path, std::forward<Args>(args)...);
		}

		void unload(std::string_view path) {
			if (auto it = hotCache.find(path); it != hotCache.end()) {
				hotCache.erase(it);
				return;
			}
			if (auto it = coldCache.find(path); it != coldCache.end()) {
				coldCache.erase(it);
			}
		}

		template<typename ...Args>
			requires ResourceCheck<T, Args...>
		std::shared_ptr<T> getOrLoad(std::string_view path, Args&&...args) {
			if (auto it = hotCache.find(path); it != hotCache.end()) {
				return it->second;
			}
			if (auto it = coldCache.find(path); it != coldCache.end()) {
				if (it->second.expired()) {
					coldCache.erase(it);
				}
				else
					return it->second.lock();
			}
			auto resource = std::make_shared<T>();
			checkCall(loadLogic(resource, path, std::forward<Args>(args)...));
			return resource;
		}

		std::shared_ptr<T> get(std::string path) {
			if (auto it = hotCache.find(path); it != hotCache.end()) {
				return it->second;
			}
			if (auto it = coldCache.find(path); it != coldCache.end()) {
				if (it->second.expired()) {
					coldCache.erase(it);
				}
				else
					return it->second.lock();
			}
			ResourceError(path, "\"get\"");
			return nullptr;
		}
	};

}