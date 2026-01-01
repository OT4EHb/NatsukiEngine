module;
#include <concepts>
export module Movement;
import ECS;
import DeltaTime;

template<class T>
concept isPosition = requires(const T & t) {
	{ t.x }->std::convertible_to<float>;
	{ t.y }->std::convertible_to<float>;
};

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

export class Movement :System {
public:
	Movement() = delete;
	template<size_t Size, ComponentType...components>
		requires findPosition<components...> && include<Velocity, components...>
	static void update(ECS<Size, components...> &ecs) {
		static DeltaTime deltaTime;
		Uint64 delta = deltaTime.update();
		size_t size = ecs.getSize();
		auto &velocitys = ecs.getComponent<Velocity>();
		for (size_t i{}; i < size; ++i) {
			auto &position =
				ecs.getComponent<
				decltype(extractPosition<components...>())
				>(i);
			position.x += velocitys[i].dx * delta;
			position.y += velocitys[i].dy * delta;
		}
	}

	template<size_t Size, ComponentType...components>
		requires include<PositionSize, components...> && include<Velocity, components...>
	static void update(ECS<Size, components...> &ecs, PositionSize rect) {
		static DeltaTime deltaTime;
		Uint64 delta = deltaTime.update();
		size_t size = ecs.getSize();
		auto &velocitys = ecs.getComponent<Velocity>();
		for (size_t i{}; i < size; ++i) {
			auto &ps = ecs.getComponent<PositionSize>(i);
			ps.x += velocitys[i].dx * delta;
			if (ps.x < rect.x) {
				velocitys[i].dx = fabs(velocitys[i].dx);
				ps.x += 10;
			}
			else if (ps.x + ps.w > rect.x + rect.w) {
				velocitys[i].dx = -fabs(velocitys[i].dx);
				ps.x -= 10;
			}

			ps.y += velocitys[i].dy * delta;
			if (ps.y < rect.y) {
				velocitys[i].dy = fabs(velocitys[i].dy);
				ps.y += 10;
			}
			else if (ps.y + ps.h > rect.y + rect.h) {
				velocitys[i].dy = -fabs(velocitys[i].dy);
				ps.y -= 10;
			}
		}
	}
};