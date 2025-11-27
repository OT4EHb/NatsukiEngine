export module RenderRect;
import ECS;
import Renderer;

export class RenderRect :System{
public:
	RenderRect() = delete;
	template<size_t Size, ComponentType...components>
		requires include<PositionSize, components...>
	static void update(ECS<Size, components...> &ecs, Renderer &ren) {
		size_t size = ecs.getSize();
		auto &rects = ecs.getComponent<PositionSize>();
		//ren.setDrawColor(ecs.getComponent<Color>(0));
		//ren.renderFillRects(rects);
		for (size_t i{}; i < size; ++i) {
			auto &rect = rects[i];
			ren.setDrawColor(ecs.getComponent<Color>(i));
			ren.renderFillRect(rect);
		}
	}
};