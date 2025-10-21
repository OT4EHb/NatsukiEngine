module;
class Window;
class Texture;
export module Renderer;
import <SDL3/SDL_render.h>;
import Window;

export class Renderer {
	friend class Texture;
private:
	SDL_Renderer *renderer;
public:
	Renderer(Window *window, const char *driverName = "");
	~Renderer();
	inline bool setDrawColor(const SDL_Color &c) const;
	inline bool clear(const SDL_Color &color = {0, 0, 0, 255}) const;
	inline bool present() const;
	inline bool renderFillRect(const SDL_FRect &rect) const;
	inline bool renderFillRects(const SDL_FRect *rects, int size) const;
	inline bool renderRect(const SDL_FRect &rect) const;
	inline bool renderRects(const SDL_FRect *rects, int size) const;
	inline bool renderLine(const SDL_FPoint &p1, const SDL_FPoint &p2) const;
	inline bool renderLines(const SDL_FPoint *points, int size) const;
	inline bool renderPoint(const SDL_FPoint &point) const;
	inline bool renderPoints(const SDL_FPoint *points, int size) const;
};

Renderer::Renderer(Window *window, const char *driverName) {
	renderer = SDL_CreateRenderer(window->window, driverName);
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

inline bool Renderer::renderFillRect(const SDL_FRect &rect) const {
	return SDL_RenderFillRect(renderer, &rect);
}

inline bool Renderer::renderFillRects(const SDL_FRect *rects, int size) const {
	return SDL_RenderFillRects(renderer, rects, size);
}

inline bool Renderer::renderRect(const SDL_FRect &rect) const {
	return SDL_RenderRect(renderer, &rect);
}

inline bool Renderer::renderRects(const SDL_FRect *rects, int size) const {
	return SDL_RenderRects(renderer, rects, size);
}

inline bool Renderer::renderLine(const SDL_FPoint &p1, const SDL_FPoint &p2) const {
	return SDL_RenderLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

inline bool Renderer::renderLines(const SDL_FPoint *points, int size) const {
	return SDL_RenderLines(renderer, points, size);
}

inline bool Renderer::renderPoint(const SDL_FPoint &point) const {
	return SDL_RenderPoint(renderer, point.x, point.y);
}

inline bool Renderer::renderPoints(const SDL_FPoint *points, int size) const {
	return SDL_RenderPoints(renderer, points, size);
}