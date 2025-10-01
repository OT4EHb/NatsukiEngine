#include <SDL.hpp>
#include<SDL3_ttf/SDL_ttf.h>

bool SDL::init(SDL_InitFlags flags) {
	return SDL_Init(flags) &&
		TTF_Init();
}

void SDL::quit() {
	TTF_Quit();
	SDL_Quit();
}

const char *SDL::getError() {
	return SDL_GetError();
}