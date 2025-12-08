export module RendererGuard;
import <SDL3/SDL_pixels.h>;
export import Renderer;

export class RendererGuard {
private:
	Renderer &renderer;
public:
	RendererGuard(Renderer &renderer, const SDL_Color &color = {0,0,0,255}) :
		renderer(renderer) {
		checkCallSDL(renderer.clear(color));
	}
	~RendererGuard() {
		checkCallSDL(renderer.present());
	}
};