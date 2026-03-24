module;
#include <concepts>
#include <cstddef>
#include <cmath>
export module Natsuki.ECS.System.Movement;
import Natsuki.ECS.System.Concept;
import Natsuki.ECS.ComponentPool;

template<class T>
concept isPosition = std::convertible_to<T, Natsuki::Position>;

template<class...Args>
concept findPosition = (isPosition<Args> || ...);

template<class T>
concept isPositionSize = std::convertible_to<T, Natsuki::PositionSize>;

template<class...Args>
concept findPositionSize = (isPositionSize<Args> || ...);

template<class B, class ...Args>
consteval auto extractPosition() {
	if constexpr (isPosition<B>) {
		return std::type_identity_t<B>{};
	}
	else
		return extractPosition<Args...>();
}

template<class B, class ...Args>
consteval auto extractPositionSize() {
	if constexpr (isPositionSize<B>) {
		return std::type_identity_t<B>{};
	}
	else
		return extractPosition<Args...>();
}

export namespace Natsuki {
	class Movement {
	public:
		Movement() = delete;
		template<ComponentType...components>
			requires findPosition<components...> &&is_one_of<Velocity, components...>
		static void update(time_type delta, ComponentPool<components...> &ecs) {
			size_t size = ecs.getSize();
			auto &velocitys = ecs.template getComponent<Velocity>();
			auto &positions = ecs.template getComponent<
				decltype(extractPosition<components...>())
			>();
			for (size_t i{}; i < size; ++i) {
				Position &position = positions[i];
				position.x += velocitys[i].dx * delta;
				position.y += velocitys[i].dy * delta;
			}
		}

		template<ComponentType...components>
			requires findPositionSize<components...> &&is_one_of<Velocity, components...>
		static void update(time_type delta, ComponentPool<components...> &ecs, PositionSize rect) {
			size_t size = ecs.getSize();
			auto &velocitys = ecs.template getComponent<Velocity>();
			auto &positions = ecs.template getComponent<
				decltype(extractPositionSize<components...>())
			>();
			for (size_t i{}; i < size; ++i) {
				PositionSize &ps = positions[i];
				ps.x += velocitys[i].dx * delta;
				if (ps.x < rect.x) {
					velocitys[i].dx = std::abs(velocitys[i].dx);
					ps.x += 10;
				}
				else if (ps.x + ps.w > rect.x + rect.w) {
					velocitys[i].dx = -std::abs(velocitys[i].dx);
					ps.x -= 10;
				}

				ps.y += velocitys[i].dy * delta;
				if (ps.y < rect.y) {
					velocitys[i].dy = std::abs(velocitys[i].dy);
					ps.y += 10;
				}
				else if (ps.y + ps.h > rect.y + rect.h) {
					velocitys[i].dy = -std::abs(velocitys[i].dy);
					ps.y -= 10;
				}
			}
		}
	};
}