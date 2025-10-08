#pragma once
#include <SDL3/SDL_render.h>

class Window;
class Texture;

class Renderer {
	friend class Texture;
private:
	SDL_Renderer *renderer;
public:
	Renderer(Window *window, const char *driverName = "");
	~Renderer();
	inline bool setDrawColor(const SDL_Color &c) const;
	inline bool clear(const SDL_Color &color = {0, 0, 0, 255}) const;
	inline bool present() const;
	inline bool fillRect(const SDL_FRect *rect) const;
	inline bool rect(const SDL_FRect *rect) const;
};

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
