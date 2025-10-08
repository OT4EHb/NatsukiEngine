#include <Texture.hpp>
#include <SDL3_image/SDL_image.h>
#include <Renderer.hpp>

Texture::Texture(Renderer *renderer, const char *file) {
	texture = IMG_LoadTexture(renderer->renderer, file);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
}