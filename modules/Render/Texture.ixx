module;
#include <string_view>
#include <SDL3_image/SDL_image.h>
export module Natsuki.Render.Texture;
import Natsuki.SDLException;

export namespace Natsuki {
	class Texture {
		friend class Renderer;
	private:
		SDL_Texture *texture{nullptr};
	public:
		constexpr inline Texture() = default;
		inline ~Texture();
		explicit inline operator SDL_Texture *() {
			return texture;
		}
		inline bool load(std::string_view, SDL_Renderer *);
		inline SDL_FPoint getSize() const;
	};
}

using namespace Natsuki;

inline bool Texture::load(std::string_view path, SDL_Renderer *renderer) {
	texture = IMG_LoadTexture(renderer, path.data());
	return texture != nullptr;
}

inline Texture::~Texture() {
	SDL_DestroyTexture(texture);
}

inline SDL_FPoint Texture::getSize() const {
	SDL_FPoint p;
	SDL_GetTextureSize(texture, &p.x, &p.y);
	return p;
}