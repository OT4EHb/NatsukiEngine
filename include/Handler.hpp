#pragma once
#include <functional>
#include <unordered_map>
#include <SDL3/SDL_init.h>

class Handler {
protected:
	using EventHandler = std::function<SDL_AppResult(SDL_Event *)>;
	std::unordered_map<SDL_EventType, EventHandler> eventHandlers;
public:
	void registerHandler(SDL_EventType type, EventHandler handler) {
		eventHandlers[type] = handler;
	}
};