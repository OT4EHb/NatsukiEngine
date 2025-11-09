export module ECS;
import <array>;
import <tuple>;
import <concepts>;
export import Components;
export import System;
export using Entity = size_t;

export template<class T, class...Args>
concept includeDerived = (std::derived_from<Args, T> || ...);

export template<class T,class...Args>
concept include = (std::same_as<T, Args> || ...);

template<class B, class D, class ...Args>
consteval auto extractDerived() {
	if constexpr (std::derived_from<D, B>) {
		return std::type_identity_t<D>{};
	}
	else
		return extractDerived<B, Args...>();
}

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

	size_t getSize() {
		return currentSize;
	}

	template <ComponentType T>
		requires include<T, components...>
	T &getComponent(Entity entity) {
		return getComponent<T>()[entity];
	}
	
	template <ComponentType T>
		requires includeDerived<T, components...>&&!include<T,components...>
	T &getComponent(Entity entity) {
		using findComponent = decltype(extractDerived<T, components...>());
		return static_cast<T&>(getComponent<findComponent>()[entity]);
	}

	template <ComponentType T>
		requires include<T, components...>
	auto &getComponent() {
		return std::get<std::array<T, Size>>(data);
	}
};