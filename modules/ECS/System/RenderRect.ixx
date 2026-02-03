module;
#include <cstddef>
export module Natsuki.ECS.System.RenderRect;
import Natsuki.ECS.ECSLogic;
import Natsuki.Render;

export namespace Natsuki {
	class RenderRect :System {
	public:
		RenderRect() = delete;
		template<ComponentType...components>
			requires include<PositionSize, components...>
		static void update(ECS<components...> &ecs, Renderer &ren) {
			size_t size = ecs.getSize();
			auto &rects = ecs.template getComponent<PositionSize>();
			//ren.setDrawColor(ecs.getComponent<Color>(0));
			//ren.renderFillRects(rects);
			for (size_t i{}; i < size; ++i) {
				auto &rect = rects[i];
				if constexpr (include<Color, components...>)
					ren.setDrawColor(ecs.template getComponent<Color>(i));
				ren.renderFillRect(rect);
			}
		}
	};
}