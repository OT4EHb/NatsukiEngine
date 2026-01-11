module;
#include <concepts>
export module Natsuki.ECS.BaseComponent;

export namespace Natsuki {
	template<class T>
	concept ComponentType = std::default_initializable<T>;
}