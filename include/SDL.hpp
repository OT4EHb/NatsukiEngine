#pragma once
#include <SDL3/SDL_init.h>

class SDL {
public:
	SDL() = delete;
	static bool init(SDL_InitFlags flags);
	static void quit();
	static const char *getError();
};