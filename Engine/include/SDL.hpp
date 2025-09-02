#pragma once
#include <SDL3/SDL.h>

class SDL {
private:
	SDL(SDL_InitFlags flags) {
		SDL_Init(flags);
	}
public:
	static void init(SDL_InitFlags flags = SDL_INIT_VIDEO) {
		static SDL instance(flags);
	}
	~SDL() {
		SDL_Quit();
	}
};