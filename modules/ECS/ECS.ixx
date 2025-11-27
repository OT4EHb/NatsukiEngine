export module ECS;
import <array>;
import <tuple>;
import <concepts>;
export import Components;
export import System;
export using Entity = size_t;

export template<class T,class...Args>
concept include = (std::same_as<T, Args> || ...);

export template <size_t Size, ComponentType...components>
class ECS {
private:
	std::tuple<std::array<components, Size>...>data{};
	size_t currentSize{};
public:
	Entity addEntity(size_t count = 1) {
		size_t res = currentSize;
		currentSize += count;
		return res;
	}

	void dropEntity(size_t index) {
		if (index < --currentSize) {
			std::apply([index, size = currentSize](auto&... comp) {
				((comp[index] = std::move(comp[size])), ...);
					   }, data);
		}
	}

	inline size_t getSize() {
		return currentSize;
	}

	template <ComponentType T>
		requires include<T, components...>
	T &getComponent(Entity entity) {
		return getComponent<T>()[entity];
	}

	template <ComponentType T>
		requires include<T, components...>
	auto &getComponent() {
		return std::get<std::array<T, Size>>(data);
	}
};