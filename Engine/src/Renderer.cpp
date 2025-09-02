#include <Renderer.hpp>

Renderer::Renderer(Window *window, const std::string &name) {
	renderer = SDL_CreateRenderer(window->window, name.c_str());
}

Renderer::Renderer(Window *window, const char *name) {
	renderer = SDL_CreateRenderer(window->window, name);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
}

const std::vector<std::string> &Renderer::getDrivers() {
	static const std::vector<std::string> drivers = []() {
		std::vector<std::string> result;
		int count = SDL_GetNumRenderDrivers();
		result.reserve(count);
		for (int i{0}; i < count; i++) {
			result.push_back(SDL_GetRenderDriver(i));
		}
		return result;
		} ();
	return drivers;
}

bool Renderer::setDrawColor(const SDL_Color &c) const {
	return SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

bool Renderer::clear(const SDL_Color &color) const {
	setDrawColor(color);
	return SDL_RenderClear(renderer);
}

bool Renderer::present() const {
	return SDL_RenderPresent(renderer);
}

bool Renderer::fillRect(const SDL_FRect *rect) const {
	return SDL_RenderFillRect(renderer, rect);
}

bool Renderer::rect(const SDL_FRect *rect) const {
	return SDL_RenderRect(renderer, rect);
}