module;
#include <concepts>
export module Component;

export std::true_type;
export std::false_type;

export template<class T>
struct traitComponent :std::false_type {};

export template<class T>
concept ComponentType = std::is_default_constructible_v<T> && traitComponent<T>::value;