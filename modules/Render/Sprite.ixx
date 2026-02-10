module;
#include <SDL3/SDL_rect.h>
export module Natsuki.Render.Sprite;
export import Natsuki.Render.Texture;
import Natsuki.ECS.ComponentPool;
import Natsuki.ECS.Component.PositionSize;

export namespace Natsuki {
	struct SpriteSrc {
		SDL_FRect srcRect;

		inline void set(const Texture &texture) {
			srcRect.x = 0;
			srcRect.y = 0;
			SDL_FPoint &p = reinterpret_cast<SDL_FPoint &>
				(*(reinterpret_cast<char *>(this) + sizeof(SDL_FPoint)));
			p = texture.getSize();
		}
	};

	struct SpriteDst {
		SDL_FRect destRect;

		inline operator Position &() {
			return reinterpret_cast<Position &>(*this);
		}

		inline operator PositionSize &() {
			return reinterpret_cast<PositionSize &>(*this);
		}
	};

	struct SpriteOrigin {
		double angle{};
		SDL_FPoint center;

		inline void setCenter(SDL_FRect &destRect) {
			center.x = destRect.w / 2;
			center.y = destRect.h / 2;
		}
	};

	template <ComponentType...components>
	struct SpritePool : public ComponentPool<SpriteSrc, SpriteDst, SpriteOrigin, components...> {
		Texture *texture{};
	};
}