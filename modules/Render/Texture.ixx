module;
#include <string_view>
#include <SDL3_image/SDL_image.h>
export module Natsuki.Render.Texture;
import Natsuki.Exception;

export using ::SDL_FPoint;

export namespace Natsuki {
	class Texture {
	private:
		SDL_Texture *texture{nullptr};
	public:
		constexpr inline Texture() = default;
		inline ~Texture() {
			SDL_DestroyTexture(texture);
		}
		SDL_Texture *getRaw() {
			return texture;
		}

		inline bool load(std::string_view path, SDL_Renderer *renderer) {
			SDL_DestroyTexture(texture);
			texture = IMG_LoadTexture(renderer, path.data());
			return texture != nullptr;
		}

		inline SDL_FPoint getSize() const {
			SDL_FPoint p;
			SDL_GetTextureSize(texture, &p.x, &p.y);
			return p;
		}
	};
}