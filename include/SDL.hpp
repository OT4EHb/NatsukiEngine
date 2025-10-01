#pragma once
#include <SDL3/SDL_init.h>
#include <Natsuki.hpp>

class NATSUKI SDL {
public:
	SDL() = delete;
	static bool init(SDL_InitFlags flags);
	static void quit();
	static const char *getError();
};