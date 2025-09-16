#pragma once
#include <GameState.hpp>

class KeyState :
	public GameState {
protected:
	std::unordered_map<SDL_Scancode, EventHandler> keyDownHandlers;
	std::unordered_map<SDL_Scancode, EventHandler> keyUpHandlers;
public:
	void registerKeyDown(SDL_Scancode type, EventHandler handler) {
		keyDownHandlers[type] = handler;
	}
	void registerKeyUp(SDL_Scancode type, EventHandler handler) {
		keyUpHandlers[type] = handler;
	}
	SDL_AppResult eventHandler(GameSystems *systems, SDL_Event *event) override {
		if (event->type == SDL_EVENT_KEY_UP) {
			auto it = keyUpHandlers.find(static_cast<SDL_Scancode>(event->key.scancode));
			if (it != keyUpHandlers.end()) {
				return it->second(systems, event);
			}
		}
		if (event->type == SDL_EVENT_KEY_DOWN) {
			auto it = keyDownHandlers.find(static_cast<SDL_Scancode>(event->key.scancode));
			if (it != keyDownHandlers.end()) {
				return it->second(systems, event);
			}
		}
		return GameState::eventHandler(systems, event);
	}
};