#pragma once
#include <functional>
#include <unordered_map>
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
	virtual void enter() {};
	virtual void exit() {};
	virtual void update(Uint64 deltaTime) = 0;
	virtual void render(Renderer*) = 0;
	virtual ~GameState() = default;
};
