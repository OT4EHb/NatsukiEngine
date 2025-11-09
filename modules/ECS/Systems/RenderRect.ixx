export module RenderRect;
import ECS;
import Renderer;

export class RenderRect :System{
public:
	RenderRect() = delete;
	template<size_t Size, ComponentType...components>
		requires include<PositionSize, components...>
	static void update(Renderer &ren, ECS<Size, components...> &ecs) {
		size_t size = ecs.getSize();
		auto &rects = ecs.getComponent<PositionSize>();
		for (size_t i{}; i < size; ++i) {
			auto &rect = rects[i].asSDL();
			ren.setDrawColor(ecs.getComponent<Color>(i).color);
			ren.renderFillRect(rect);
		}
	}
};