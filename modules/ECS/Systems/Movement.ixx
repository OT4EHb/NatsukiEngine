export module Movement;
import ECS;
import GlobalTime;

export class Movement :System {
public:
	Movement() = delete;
	template<size_t Size, ComponentType...components>
		requires includeDerived<Position, components...> &&include<Velocity, components...>
	static void update(ECS<Size, components...> &ecs) {
		auto delta = GlobalTime::getDelta();
		size_t size = ecs.getSize();
		auto &velocitys = ecs.getComponent<Velocity>();
		for (size_t i{}; i < size; ++i) {
			auto &position = ecs.getComponent<Position>(i);
			position.x += velocitys[i].dx * delta;
			position.y += velocitys[i].dy * delta;
		}
	}

	template<size_t Size, ComponentType...components>
		requires includeDerived<Position, components...> &&include<Velocity, components...>
	static void update(ECS<Size, components...> &ecs, PositionSize rect) {
		auto delta = GlobalTime::getDelta();
		size_t size = ecs.getSize();
		auto &velocitys = ecs.getComponent<Velocity>();
		for (size_t i{}; i < size; ++i) {
			auto &position = ecs.getComponent<Position>(i);
			position.x += velocitys[i].dx * delta;
			if (position.x < rect.x || position.x>rect.x + rect.width) {
				velocitys[i].dx *= -1;
				velocitys[i].dy += 0.1f;
			}
			position.y += velocitys[i].dy * delta;
			if (position.y < rect.y || position.y>rect.y + rect.height) {
				velocitys[i].dy *= -1;
				velocitys[i].dx += 0.1f;
			}
		}
	}
};