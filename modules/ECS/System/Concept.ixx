module;
#include <concepts>
export module Natsuki.ECS.System.Concept;
export import Natsuki.Time;

export namespace Natsuki {
	template<class T, class...Args>
	concept DinamicSystem = requires(time_type delta, Args...args) {
		T::update(delta, args...);
	};

	template<class T, class...Args>
	concept StaticSystem = requires(Args... args) {
		T::update(args...);
	};

	template<class T, class...Args>
	concept SystemType = StaticSystem<T, Args...> || DinamicSystem<T, Args...>;
}