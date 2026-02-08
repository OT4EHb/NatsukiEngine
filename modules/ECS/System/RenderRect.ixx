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
			for (auto i:ecs){
				auto &rect = ecs.template getComponent<PositionSize>(i);
				if constexpr (include<Color, components...>)
					ren.setDrawColor(ecs.template getComponent<Color>(i));
				ren.renderFillRect(rect);
			}
		}
	};
}