module;
class Window;
export module Renderer;
import <string_view>;
import <SDL3/SDL_render.h>;
import Window;
import SDLException;

export class Renderer {
	friend class Texture;
	friend class FPSDisplay;
private:
	SDL_Renderer *renderer;
public:
	Renderer(Window &window, std::string_view driverName = "");
	~Renderer();
	inline bool setDrawColor(const SDL_Color &c) const;
	inline SDL_Color getDrawColor() const;
	inline bool setScale(const SDL_FPoint) const;
	inline SDL_FPoint getScale() const;
	inline bool clear(const SDL_Color &color = {0, 0, 0, 255}) const;
	inline bool present() const;
	inline bool setVSync(int vsync = 1) const;
	inline bool renderFillRect(const SDL_FRect &rect) const;
	inline bool renderFillRects(const SDL_FRect *rects, int size) const;
	inline bool renderRect(const SDL_FRect &rect) const;
	inline bool renderRects(const SDL_FRect *rects, int size) const;
	inline bool renderLine(const SDL_FPoint &p1, const SDL_FPoint &p2) const;
	inline bool renderLines(const SDL_FPoint *points, int size) const;
	inline bool renderPoint(const SDL_FPoint &point) const;
	inline bool renderPoints(const SDL_FPoint *points, int size) const;
};

Renderer::Renderer(Window &window, std::string_view driverName) {
	renderer = SDL_CreateRenderer(window.window, driverName.data());
	checkCallSDL(renderer != nullptr);
}

Renderer::~Renderer() {
	SDL_DestroyRenderer(renderer);
}

inline bool Renderer::setDrawColor(const SDL_Color &c) const {
	return SDL_SetRenderDrawColor(renderer, c.r, c.g, c.b, c.a);
}

inline SDL_Color Renderer::getDrawColor() const {
	SDL_Color color;
	SDL_GetRenderDrawColor(renderer, &color.r, &color.g, &color.b, &color.a);
	return color;
}

inline bool Renderer::setScale(const SDL_FPoint scale) const {
	return SDL_SetRenderScale(renderer, scale.x, scale.y);
}

inline SDL_FPoint Renderer::getScale() const {
	SDL_FPoint scale;
	SDL_GetRenderScale(renderer, &scale.x, &scale.y);
	return scale;
}

inline bool Renderer::clear(const SDL_Color &color) const {
	setDrawColor(color);
	return SDL_RenderClear(renderer);
}

inline bool Renderer::present() const {
	return SDL_RenderPresent(renderer);
}

inline bool Renderer::setVSync(int vsync) const {
	return SDL_SetRenderVSync(renderer, vsync);
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