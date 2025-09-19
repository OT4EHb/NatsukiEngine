#pragma once
#include <SDL3/SDL_init.h>
#include <GameState.hpp>

class Game {
public:
	virtual SDL_AppResult iterate() = 0;
	virtual SDL_AppResult eventHandler(SDL_Event *) = 0;
};