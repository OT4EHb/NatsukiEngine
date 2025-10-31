export module SourceManager;
import <unordered_map>;
import <string>;
import <memory>;

export template<typename T>
class SourceManager {
private:
	std::unordered_map<std::string, std::shared_ptr<T> > resources;
public:
	SourceManager() = default;
	~SourceManager() = default;

	template<typename ...Args>
		requires std::is_constructible_v<T, Args...>
	void create(const std::string& name, Args&&...args) {
		if (resources.find(name) != resources.end()) return;
		auto resource = std::make_shared<T>(std::forward<Args>(args)...);
		resources[name] = resource;
	}

	void release(const std::string& name) {
		auto res = resources.find(name);
		if (res != resources.end()) {
			resources.erase(res);
		}
	}

	std::shared_ptr<T> get(const std::string &name) {
		auto res = resources.find(name);
		if (res != resources.end()) {
			return res->second;
		}
		return nullptr;
	}
};