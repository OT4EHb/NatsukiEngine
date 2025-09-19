#pragma once
#include <functional>
#include <unordered_map>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_init.h>

class GameSystems;

class GameState {
protected:
	using EventHandler = std::function<SDL_AppResult(GameSystems *, SDL_Event *)>;
	std::unordered_map<SDL_EventType, EventHandler> eventHandlers;
public:
	void registerHandler(SDL_EventType type, EventHandler handler) {
		eventHandlers[type] = handler;
	}
	virtual SDL_AppResult eventHandler(GameSystems *systems, SDL_Event *event) const {
		auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
		if (it != eventHandlers.end()) {
			return it->second(systems, event);
		}
		return SDL_APP_CONTINUE;
	}
	virtual void enter() {};
	virtual void exit() {};
	virtual void update(Uint64 deltaTime) = 0;
	virtual void render() = 0;
	virtual ~GameState() = default;
};
