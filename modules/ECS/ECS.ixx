export module ECS;
import <array>;
import <tuple>;
import <concepts>;
export import Components;
export using Entity = size_t;

export template<class T, class...Args>
concept includes = (std::is_same_v<T, Args> || ...);

export template <size_t Size, ComponentType...components>
class ECS {
private:
	std::tuple<std::array<components, Size>...>data{};
	size_t currentSize{};
public:
	Entity addEntity() {
		return currentSize++;
	}

	size_t getSize() {
		return currentSize;
	}

	template <ComponentType T>
	T &getComponent(Entity entity) {
		return std::get<std::array<T, Size>>(data)[entity];
	}

	template <ComponentType T>
	auto &getComponent() {
		return std::get<std::array<T, Size>>(data);
	}
};