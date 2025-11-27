export module Component;
export import <concepts>;

export template<class T>
struct traitComponent :std::false_type {};

export template<class T>
concept ComponentType = std::is_default_constructible_v<T> && traitComponent<T>::value;