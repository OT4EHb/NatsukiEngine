#pragma once
#include <Window.hpp>
#include <vector>
#include <string>
class Renderer {
private:
	SDL_Renderer *renderer;
public:
	Renderer(Window *window, const std::string &name) {
		renderer = SDL_CreateRenderer(window->window, name.c_str());
	}

	Renderer(Window *window, const char *name = nullptr) {
		renderer = SDL_CreateRenderer(window->window, name);
	}

	~Renderer() {
		SDL_DestroyRenderer(renderer);
	}

	static const std::vector<std::string> &getDrivers() {
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

	bool setDrawColor(const SDL_Color &c) const {
		return SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
	}

	bool clear(const SDL_Color &color = {0, 0, 0, 255}) const {
		setDrawColor(color);
		return SDL_RenderClear(renderer);
	}

	bool present() const {
		return SDL_RenderPresent(renderer);
	}

	bool fillRect(const SDL_FRect *rect) const {
		return SDL_RenderFillRect(renderer, rect);
	}

	bool rect(const SDL_FRect *rect) const {
		return SDL_RenderRect(renderer, rect);
	}
};