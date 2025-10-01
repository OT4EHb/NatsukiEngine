#include <SDL3/SDL_render.h>
#include <Window.hpp>
#include <Renderer.hpp>

Renderer::Renderer(Window *window, const char *name) {
	renderer = SDL_CreateRenderer(window->window, name);
}

Renderer::~Renderer() {
		SDL_DestroyRenderer(renderer);
	}

inline bool Renderer::setDrawColor(const SDL_Color &c) const {
	return SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

inline bool Renderer::clear(const SDL_Color &color) const {
	setDrawColor(color);
	return SDL_RenderClear(renderer);
}

inline bool Renderer::present() const {
	return SDL_RenderPresent(renderer);
}

inline bool Renderer::fillRect(const SDL_FRect *rect) const {
	return SDL_RenderFillRect(renderer, rect);
}

inline bool Renderer::rect(const SDL_FRect *rect) const {
	return SDL_RenderRect(renderer, rect);
}