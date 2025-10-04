#pragma once
#include <Handler.hpp>

class Context;

class GameState : Handler {
public:
	virtual SDL_AppResult eventHandler(Context&,SDL_Event *event) const {
		auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
		if (it != eventHandlers.end()) {
			return it->second(event);
		}
		return SDL_APP_CONTINUE;
	}
	virtual void enter(Context &) {};
	virtual void exit(Context &) {};
	virtual SDL_AppResult iterate(Context &) = 0;
	virtual ~GameState() = default;
};
