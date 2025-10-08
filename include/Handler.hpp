#pragma once
#include <functional>
#include <unordered_map>
#include <SDL3/SDL_init.h>

class Context;

class Handler {
protected:
	using EventHandler = std::function<SDL_AppResult(Context&,SDL_Event *)>;
	std::unordered_map<SDL_EventType, EventHandler> eventHandlers;
public:
	inline void registerHandler(SDL_EventType type, EventHandler handler) {
		eventHandlers[type] = handler;
	}
};