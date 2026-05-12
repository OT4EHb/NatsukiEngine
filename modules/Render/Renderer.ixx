module;
#include <string_view>
#include <span>
#include <SDL3/SDL_render.h>
export module Natsuki.Render.Renderer;
import Natsuki.Window;
export import Natsuki.Exception;
export import Natsuki.Render.Sprite;

export using ::SDL_Vertex;

export namespace Natsuki {
	class Renderer {
	private:
		SDL_Renderer *renderer;
	public:
		Renderer(Window &window, std::string_view driverName = "");
		~Renderer();
		SDL_Renderer *getRaw() {
			return renderer;
		}

		inline bool setDrawColor(const SDL_Color &c) const;
		inline SDL_Color getDrawColor() const;

		inline bool setScale(const FPoint) const;
		inline FPoint getScale() const;

		inline bool clear(const SDL_Color &color = {0, 0, 0, 255}) const;
		inline bool present() const;
		inline bool setVSync(int vsync = 1) const;

		inline bool renderFillRect(const FRect &rect) const;
		inline bool renderFillRects(std::span<const FRect>) const;

		inline bool render(const FRect &rect) const;
		inline bool render(std::span<const FRect>) const;

		inline bool renderLine(const FPoint &p1, const FPoint &p2) const;
		inline bool renderLines(std::span<const FPoint>) const;

		inline bool render(const FPoint &point) const;
		inline bool render(std::span<const FPoint>) const;

		inline bool renderGeometry(std::span<const SDL_Vertex>,
								   std::span <const int> = {},
								   SDL_Texture * = nullptr) const;
		inline bool render(Texture &, const FRect &src, const FRect &dst) const;
		inline bool render(Texture &, const FRect &src, const FRect &dst,
						   const SpriteOrigin &, FlipMode) const;
		inline bool render(Sprite&) const;

		inline bool renderDebugText(std::string_view, FPoint = {0.f, 0.f}) const;
	};
}

using namespace Natsuki;

Renderer::Renderer(Window &window, std::string_view driverName) {
	renderer = SDL_CreateRenderer(window.getRaw(), driverName.data());
	checkCall(renderer != nullptr);
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

inline bool Renderer::setScale(const FPoint scale) const {
	return SDL_SetRenderScale(renderer, scale.x, scale.y);
}

inline FPoint Renderer::getScale() const {
	FPoint scale;
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

inline bool Renderer::renderFillRect(const FRect &rect) const {
	return SDL_RenderFillRect(renderer, &rect);
}

inline bool Renderer::renderFillRects(std::span<const FRect>rects) const {
	return SDL_RenderFillRects(renderer, rects.data(), static_cast<int>(rects.size()));
}

inline bool Renderer::render(const FRect &rect) const {
	return SDL_RenderRect(renderer, &rect);
}

inline bool Renderer::render(std::span<const FRect>rects) const {
	return SDL_RenderRects(renderer, rects.data(), static_cast<int>(rects.size()));
}

inline bool Renderer::renderLine(const FPoint &p1, const FPoint &p2) const {
	return SDL_RenderLine(renderer, p1.x, p1.y, p2.x, p2.y);
}

inline bool Renderer::renderLines(std::span<const FPoint>points) const {
	return SDL_RenderLines(renderer, points.data(), static_cast<int>(points.size()));
}

inline bool Renderer::render(const FPoint &point) const {
	return SDL_RenderPoint(renderer, point.x, point.y);
}

inline bool Renderer::render(std::span<const FPoint>points) const {
	return SDL_RenderPoints(renderer, points.data(), static_cast<int>(points.size()));
}

inline bool Renderer::renderGeometry(std::span<const SDL_Vertex>vertices,
									 std::span<const int>indices, SDL_Texture *texture) const {
	return SDL_RenderGeometry(renderer, texture,
							  vertices.data(), static_cast<int>(vertices.size()),
							  indices.data(), static_cast<int>(indices.size())
	);
}

inline bool Renderer::render(Texture &texture, const FRect &src,
							 const FRect &dst) const {
	return SDL_RenderTexture(renderer, texture.getRaw(), &src, &dst);
}

inline bool Renderer::render(Texture &texture, const FRect &src, const FRect &dst,
							 const SpriteOrigin &origin, FlipMode flip) const {
	return SDL_RenderTextureRotated(renderer, texture.getRaw(), &src,
									&dst, origin.angle,
									&origin.center, flip);
}

inline bool Renderer::render(Sprite &spr) const {
	return render(*spr.texture.get(), spr.src, spr.dst, spr.origin, spr.flip);
}

inline bool Renderer::renderDebugText(std::string_view text, FPoint position) const {
	return SDL_RenderDebugText(renderer, position.x, position.y, text.data());
}