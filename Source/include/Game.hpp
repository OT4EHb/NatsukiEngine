#pragma once
#include <SDL3/SDL_init.h>
#include <GameState.hpp>

class Game {
protected:
	GameState *current = nullptr;
public:
	virtual ~Game() = 0;
	virtual SDL_AppResult iterate() = 0;
	virtual SDL_AppResult eventHandler(SDL_Event *) = 0;
	void changeState(GameState*state) {
		current->exit();
		delete current;
		current = state;
		current->enter();
	}
};