module;
class Renderer;
export module RendererGuard;
export import Renderer;

export class RendererGuard {
private:
	Renderer *renderer;
public:
	RendererGuard(Renderer *renderer):renderer(renderer) {
		renderer->clear();
	}
	~RendererGuard() {
		renderer->present();
	}
};