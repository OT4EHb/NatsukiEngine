#include <Renderer.hpp>
#include <Window.hpp>

Renderer::Renderer(Window *window, const char *driverName) {
	renderer = SDL_CreateRenderer(window->window, driverName);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
}