module;
#include <concepts>
export module Natsuki.ECS.BaseSystem;

export namespace Natsuki {
	class System {};

	template<class T>
	concept SystemType = std::derived_from<T, System>;
}