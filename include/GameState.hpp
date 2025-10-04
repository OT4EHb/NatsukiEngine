#pragma once
#include <Handler.hpp>

class GameState : Handler {
public:
	virtual SDL_AppResult eventHandler(SDL_Event *event) const {
		auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
		if (it != eventHandlers.end()) {
			return it->second(event);
		}
		return SDL_APP_CONTINUE;
	}
	virtual void enter(GAME*) {};
	virtual void exit(GAME *) {};
	virtual SDL_AppResult iterate(GAME *) = 0;
	virtual ~GameState() = default;
};
