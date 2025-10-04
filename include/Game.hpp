#pragma once
#include <SDL3/SDL_init.h>

class Context;

class Game {
public:
	Game() = delete;
	static SDL_AppResult iterate(Context&);
	static SDL_AppResult eventHandler(Context&,SDL_Event *);
};