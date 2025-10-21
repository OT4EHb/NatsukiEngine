module;
class Surface;
export module Texture;
import <SDL3_image/SDL_image.h>;
export import Renderer;

export class Texture {
private:
	SDL_Texture *texture;
	Renderer &renderer;
public:
	inline Texture(Renderer &renderer, const char *file);
	//inline Texture(Renderer *renderer, Surface *surface);
	inline ~Texture();
	inline bool render(const SDL_FRect *srcrect = nullptr, const SDL_FRect *dstrect = nullptr) const;
};

Texture::Texture(Renderer &renderer, const char *file) :
	renderer(renderer) {
	texture = IMG_LoadTexture(renderer.renderer, file);
}

Texture::~Texture() {
	SDL_DestroyTexture(texture);
}

bool Texture::render(const SDL_FRect *srcrect, const SDL_FRect *dstrect) const {
	return SDL_RenderTexture(renderer.renderer, texture, srcrect, dstrect);
}