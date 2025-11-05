export module Movement;
import System;
import ECS;
import GlobalTime;

export class Movement :public System {
public:
	Movement() = delete;
	template<size_t Size, ComponentType...components>
		requires includes<Position, components...> &&includes<Velocity, components...>
	static void update(ECS<Size, components...> &ecs) {
		auto delta = GlobalTime::getDelta();
		size_t size = ecs.getSize();
		auto &positions = ecs.getComponent<Position>();
		auto &velocitys = ecs.getComponent<Velocity>();
		for (size_t i{}; i < size; ++i) {
			positions[i].x += velocitys[i].dx * delta;
			positions[i].y += velocitys[i].dy * delta;
		}
	}
};