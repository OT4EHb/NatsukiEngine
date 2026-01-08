module;
#include <functional>
#include <unordered_map>
#include <SDL3/SDL_init.h>
export module Natsuki.GameState.BaseGameState;

export namespace Natsuki {
	class BaseGameState {
	protected:
		using EventHandler = std::function<void(SDL_Event *)>;
		std::unordered_map<SDL_EventType, EventHandler> eventHandlers;
	public:
		inline void registerHandler(SDL_EventType type, EventHandler handler) {
			eventHandlers[type] = handler;
		}
		virtual void eventHandler(SDL_Event *event) const {
			auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
			if (it != eventHandlers.end()) {
				it->second(event);
			}
		}
		virtual void enter() {};
		virtual void exit() {};
		virtual void iterate() = 0;
		virtual ~BaseGameState() = default;
	};

	export using GameState = BaseGameState;
}