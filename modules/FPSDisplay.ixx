export module FPSDisplay;
import Renderer;
import <string>;
import <SDL3/SDL_render.h>;
import GlobalTime;

export class FPSDisplay {
public:
	FPSDisplay() = delete;
	static void render(Renderer &ren) {
		static std::string fps{};
		constexpr SDL_Color color{255, 0, 0, 255};
		fps = std::to_string(static_cast<Uint64>(round(1000. / GlobalTime::getDelta())));
		SDL_Color tmpColor = ren.getDrawColor();
		SDL_FPoint scale = ren.getScale();
		ren.setDrawColor(color);
		ren.setScale({2.f * scale.x, 2.f * scale.y});
		SDL_RenderDebugText(ren.renderer, 0, 0, fps.c_str());
		ren.setDrawColor(tmpColor);
		ren.setScale(scale);
	}
};