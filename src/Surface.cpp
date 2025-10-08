#include <Surface.hpp>
#include <SDL3_image/SDL_image.h>

Surface::Surface(const char *file) {
	surface = IMG_Load(file);
}

Surface::~Surface() {
	SDL_DestroySurface(surface);
}