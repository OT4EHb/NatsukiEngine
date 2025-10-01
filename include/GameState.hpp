#pragma once
#include <Handler.hpp>

class Game;

class GameState : Handler {
public:
	virtual SDL_AppResult eventHandler(SDL_Event *event) const {
		auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
		if (it != eventHandlers.end()) {
			return it->second(event);
		}
		return SDL_APP_CONTINUE;
	}
	virtual void enter(Game*) {};
	virtual void exit(Game *) {};
	virtual SDL_AppResult iterate(Game *) = 0;
	virtual ~GameState() = default;
};
