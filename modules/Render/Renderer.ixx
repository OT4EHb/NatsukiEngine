export module Renderer;
import <string_view>;
export import <span>;
import <SDL3/SDL_render.h>;
import Window;
import SDLException;
import CategoryLog;

export SDL_Vertex;
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
	inline bool renderFillRects(std::span<const SDL_FRect>) const;
	inline bool renderRect(const SDL_FRect &rect) const;
	inline bool renderRects(std::span<const SDL_FRect>) const;
	inline bool renderLine(const SDL_FPoint &p1, const SDL_FPoint &p2) const;
	inline bool renderLines(std::span<const SDL_FPoint>) const;
	inline bool renderPoint(const SDL_FPoint &point) const;
	inline bool renderPoints(std::span<const SDL_FPoint>) const;
	inline bool renderGeometry(std::span<const SDL_Vertex>,
							   std::span <const int> = {},
							   SDL_Texture * = nullptr) const;
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

inline bool Renderer::renderFillRects(std::span<const SDL_FRect>rects) const {
	return SDL_RenderFillRects(renderer, rects.data(), static_cast<int>(rects.size()));
}

inline bool Renderer::renderRect(const SDL_FRect &rect) const {
	return SDL_RenderRect(renderer, &rect);
}

inline bool Renderer::renderRects(std::span<const SDL_FRect>rects) const {
	return SDL_RenderRects(renderer, rects.data(), static_cast<int>(rects.size()));
}

inline bool Renderer::renderLine(const SDL_FPoint &p1, const SDL_FPoint &p2) const {
	return SDL_RenderLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

inline bool Renderer::renderLines(std::span<const SDL_FPoint>points) const {
	return SDL_RenderLines(renderer, points.data(), static_cast<int>(points.size()));
}

inline bool Renderer::renderPoint(const SDL_FPoint &point) const {
	return SDL_RenderPoint(renderer, point.x, point.y);
}

inline bool Renderer::renderPoints(std::span<const SDL_FPoint>points) const {
	return SDL_RenderPoints(renderer, points.data(), static_cast<int>(points.size()));
}

inline bool Renderer::renderGeometry(std::span<const SDL_Vertex>vertices,
									 std::span<const int>indices, SDL_Texture *texture) const {
	return SDL_RenderGeometry(renderer, texture,
							  vertices.data(), static_cast<int>(vertices.size()),
							  indices.data(), static_cast<int>(indices.size())
	);
}