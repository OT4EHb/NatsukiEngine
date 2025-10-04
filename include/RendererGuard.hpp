#pragma once
#include <Renderer.hpp>

class RendererGuard {
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