module;
#include <concepts>
#include <cstddef>
#include <cmath>
export module Natsuki.ECS.System.Movement;
import Natsuki.ECS.ECSLogic;
import Natsuki.Time;

template<class T>
concept isPosition = std::convertible_to<T, Natsuki::Position>;

template<class...Args>
concept findPosition = (isPosition<Args> || ...);

template<class B, class ...Args>
consteval auto extractPosition() {
	if constexpr (isPosition<B>) {
		return std::type_identity_t<B>{};
	}
	else
		return extractPosition<Args...>();
}

export namespace Natsuki {
	class Movement :System {
	public:
		Movement() = delete;
		template<ComponentType...components>
			requires findPosition<components...> &&include<Velocity, components...>
		static void update(ECS<components...> &ecs) {
			static DeltaTime deltaTime;
			auto delta = deltaTime.update();
			size_t size = ecs.getSize();
			auto &velocitys = ecs.template getComponent<Velocity>();
			auto &positions = ecs.template getComponent<decltype(extractPosition<components...>())>();
			for (size_t i{}; i < size; ++i) {
				auto &position = positions[i];
					/*ecs.template getComponent<
					decltype(extractPosition<components...>())
					>(i);*/
				position.x += velocitys[i].dx * delta;
				position.y += velocitys[i].dy * delta;
			}
		}

		template<ComponentType...components>
			requires include<PositionSize, components...> &&include<Velocity, components...>
		static void update(ECS<components...> &ecs, PositionSize rect) {
			static DeltaTime deltaTime;
			auto delta = deltaTime.update();
			size_t size = ecs.getSize();
			auto &velocitys = ecs.template getComponent<Velocity>();
			auto &positions =ecs.template getComponent<PositionSize>();
			for (size_t i{}; i < size; ++i) {
				auto &ps = positions[i];
					//ecs.template getComponent<PositionSize>(i);
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