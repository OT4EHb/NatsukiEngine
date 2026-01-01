#include <string_view>
#include <SDL3_image/SDL_image.h>
export module Texture;
import SDLException;

export class Texture {
	friend class Renderer;
private:
	SDL_Texture *texture;
public:
	inline Texture(SDL_Renderer* renderer, std::string_view file);
	//inline Texture(Renderer *renderer, Surface *surface);
	explicit inline operator SDL_Texture *() {
		return texture;
	}
	inline ~Texture();
	inline SDL_FPoint getSize() const;
};

Texture::Texture(SDL_Renderer *renderer, std::string_view file) {
	texture = IMG_LoadTexture(renderer, file.data());
	checkCallSDL(texture != nullptr);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
}

inline SDL_FPoint Texture::getSize() const {
	SDL_FPoint p;
	SDL_GetTextureSize(texture, &p.x, &p.y);
	return p;
}