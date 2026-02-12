module;
#include <memory>
#include <SDL3/SDL_rect.h>
export module Natsuki.Render.Sprite;
export import Natsuki.Render.FlipMode;
export import Natsuki.Render.Texture;
export import Natsuki.ECS.ComponentPool;
export import Natsuki.ECS.Component.PositionSize;

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

		constexpr inline operator SDL_FRect &() {
			return srcRect;
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

	struct Sprite {
		Texture texture;
		SpriteSrc src;
		SDL_FRect dest;
		SpriteOrigin origin;
		FlipMode flip;
	};

	template <ComponentType...components>
	struct SpritePool : public ComponentPool<SpriteSrc, PositionSize, SpriteOrigin, components...> {
		std::shared_ptr<Texture> texture;
	};
}