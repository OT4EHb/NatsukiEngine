export module Component;
import <concepts>;

export struct Component {};

export template<class T>
concept ComponentType = std::is_base_of_v<Component, T> &&
std::is_default_constructible_v<T>;