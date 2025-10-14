export module SourceManager;
import <unordered_map>;
import <string>;

export template<typename T>
class SourceManager {
private:
	std::unordered_map<std::string, T*> resources;
public:
	SourceManager() = default;
	~SourceManager() = default;

	template<typename ...Args>
		requires std::is_constructible_v<T, Args...>
	T* create(const std::string &name, Args&&...args) {
		if (resources.find(name) != resources.end()) return resources[name];
		auto resource = new T(std::forward<Args>(args)...);
		resources[name] = resource;
		return resource;
	}

	void release(const std::string &name) {
		auto res = resources.find(name);
		if (res != resources.end()) {
			resources.erase(res);
		}
	}

	T* get(const std::string &name) {
		auto res = resources.find(name);
		if (res != resources.end()) {
			return res->second;
		}
		return nullptr;
	}
};