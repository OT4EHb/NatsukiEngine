module;
struct SDL_Texture;
export module Texture;
import <SDL3_image/SDL_image.h>;
export import Renderer;

export class Texture {
private:
	SDL_Texture *texture;
public:
	inline Texture(Renderer *renderer, const char *file);
	inline ~Texture();
};

Texture::Texture(Renderer *renderer, const char *file) {
	texture = IMG_LoadTexture(renderer->renderer, file);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
}