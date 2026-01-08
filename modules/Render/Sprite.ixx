module;
#include <SDL3/SDL_rect.h>
export module Natsuki.Render.Sprite;
export import Natsuki.Render.Texture;

export namespace Natsuki {
	class Sprite {
		friend class Renderer;
	private:
		Texture &texture;
	public:
		SDL_FRect src;

		SDL_FRect dst;
		double angle{};
		SDL_FPoint centerRotated;
	public:
		inline Sprite(Texture &texture, const SDL_FRect &rect) :
			texture(texture), src(rect),
			dst{.x = 0, .y = 0, .w = rect.w, .h = rect.h} {
			setCenter();
		}

		inline Sprite(const Sprite &other) = default;
		inline Sprite(Sprite &&other) = default;

		inline SDL_FPoint &getPosition() {
			return reinterpret_cast<SDL_FPoint &>(dst);
		}

		inline void setCenter(SDL_FPoint p) {
			centerRotated = p;
		}
		inline void setCenter() {
			centerRotated.x = dst.w / 2;
			centerRotated.y = dst.h / 2;
		}
	};
}