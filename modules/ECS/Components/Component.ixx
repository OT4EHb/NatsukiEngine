export module Component;
import <concepts>;

export struct Component {
	using componentTag = void;
};

export template<class T>
concept ComponentType = std::is_default_constructible_v<T> &&
	requires{
	typename T::componentTag;
};