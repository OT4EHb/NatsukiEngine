module;
#include <string>
#include <SDL3/SDL_render.h>
export module Natsuki.FPSDisplay;
import Natsuki.Render;
import Natsuki.Time;

export namespace Natsuki {
	class FPSDisplay {
	public:
		FPSDisplay() = delete;
		static void render(Renderer &ren) {
			constexpr SDL_Color color{255, 0, 0, 255};
			SDL_Color tmpColor = ren.getDrawColor();
			SDL_FPoint scale = ren.getScale();
			ren.setDrawColor(color);
			ren.setScale({2.f * scale.x, 2.f * scale.y});
			SDL_RenderDebugText(static_cast<SDL_Renderer *>(ren), 0, 0, fps.c_str());
			ren.setDrawColor(tmpColor);
			ren.setScale(scale);
			delta = deltaTime.update();
		}
		static void update() {
			fps = std::to_string(
				static_cast<Uint64>(
					//lround(
					(1'000'000'000 / delta)
					//)
					)
			);
			//count = 0;
			delta = 1;
		}
	private:
		static inline std::string fps;
		static inline DeltaTimeNS deltaTime;
		static inline Uint64 delta{1};
		static inline Uint64 count;
	};
}