export module Movement;
import ECS;
import DeltaTime;

export class Movement :System {
public:
	Movement() = delete;
	template<size_t Size, ComponentType...components>
		requires includeDerived<Position, components...> &&include<Velocity, components...>
	static void update(ECS<Size, components...> &ecs) {
		static DeltaTime deltaTime;
		Uint64 delta = deltaTime.update();
		size_t size = ecs.getSize();
		auto &velocitys = ecs.getComponent<Velocity>();
		for (size_t i{}; i < size; ++i) {
			auto &position = ecs.getComponent<Position>(i);
			position.x += velocitys[i].dx * delta;
			position.y += velocitys[i].dy * delta;
		}
	}

	template<size_t Size, ComponentType...components>
		requires include<PositionSize, components...> &&include<Velocity, components...>
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
			else if (ps.x + ps.width > rect.x + rect.width) {
				velocitys[i].dx = -fabs(velocitys[i].dx);
				ps.x -= 10;
			}

			ps.y += velocitys[i].dy * delta;
			if (ps.y < rect.y) {
				velocitys[i].dy = fabs(velocitys[i].dy);
				ps.y += 10;
			}
			else if (ps.y + ps.height > rect.y + rect.height) {
				velocitys[i].dy = -fabs(velocitys[i].dy);
				ps.y -= 10;
			}
		}
	}
};