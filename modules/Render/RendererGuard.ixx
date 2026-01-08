module;
#include <SDL3/SDL_pixels.h>
export module Natsuki.Render.RendererGuard;
export import Natsuki.Render.Renderer;

export namespace Natsuki {
	class RendererGuard {
	private:
		Renderer &renderer;
	public:
		RendererGuard(Renderer &renderer, const SDL_Color &color = {0, 0, 0, 255}) :
			renderer(renderer) {
			checkCallSDL(renderer.clear(color));
		}
		~RendererGuard() {
			checkCallSDL(renderer.present());
		}
	};
}