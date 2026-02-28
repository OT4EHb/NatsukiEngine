module;
#include <concepts>
export module Natsuki.ECS.Component.Concept;

export namespace Natsuki {
	template<class T>
	concept ComponentType = std::default_initializable<T>;
}