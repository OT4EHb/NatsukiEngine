module;
#include <initializer_list>
#include <unordered_map>
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_events.h>
export module Natsuki.GameState.KeyState;
export import Natsuki.GameState.BaseGameState;

export namespace Natsuki {
	class KeyState :
		public GameState {
	protected:
		std::unordered_map<SDL_Scancode, EventHandler> keyDownHandlers;
		std::unordered_map<SDL_Scancode, EventHandler> keyUpHandlers;
	public:
		inline void registerKeyDown(const SDL_Scancode type, EventHandler handler) {
			keyDownHandlers[type] = handler;
		}
		void registerKeyDown(std::initializer_list<const SDL_Scancode> types, EventHandler handler) {
			for (const SDL_Scancode &type : types)
				registerKeyDown(type, handler);
		}
		inline void registerKeyUp(const SDL_Scancode type, EventHandler handler) {
			keyUpHandlers[type] = handler;
		}
		void registerKeyUp(std::initializer_list<SDL_Scancode> types, EventHandler handler) {
			for (const SDL_Scancode &type : types)
				registerKeyUp(type, handler);
		}
		void eventHandler(SDL_Event *event) const override {
			if (event->type == SDL_EVENT_KEY_UP) {
				auto it = keyUpHandlers.find(static_cast<SDL_Scancode>(event->key.scancode));
				if (it != keyUpHandlers.end()) {
					it->second(event);
				}
				return;
			}
			if (event->type == SDL_EVENT_KEY_DOWN) {
				auto it = keyDownHandlers.find(static_cast<SDL_Scancode>(event->key.scancode));
				if (it != keyDownHandlers.end()) {
					it->second(event);
				}
				return;
			}
			GameState::eventHandler(event);
		}
	};
}