module;
#include <concepts>
export module Natsuki.ECS.System.Concept;
export import Natsuki.Time.DeltaTime;

export namespace Natsuki {
	template<class T, class...Args>
	concept DinamicSystem = requires(DeltaTime delta, Args...args) {
		T::update(delta, args...);
	};

	template<class T, class...Args>
	concept StaticSystem = requires(Args... args) {
		T::update(args...);
	};

	template<class T, class...Args>
	concept SystemType = StaticSystem<T, Args...> || DinamicSystem<T, Args...>;
}