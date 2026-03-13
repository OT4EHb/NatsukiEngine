module;
#include <array>
#include <concepts>
#include <functional>
#include <unordered_map>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
export module Natsuki.Event.EventHandler;
export import Natsuki.Event.KeySystem;
export import Natsuki.Event.MouseSystem;


export namespace Natsuki {
	class EventHandler {
	private:
		using Event = SDL_Event &;
		using handler_type = std::function<SDL_AppResult(Event)>;
		using event_t = Uint32;
		std::unordered_map<event_t, handler_type> handlers;
	public:
		KeySystem key;
		MouseSystem mouse;

		template<class F>
			requires std::invocable<F, Event>
		void set(SDL_EventType type, F &&f) {
			handlers[static_cast<event_t>(type)] = std::forward<handler_type>(make_handler<F, Event>(std::forward<F>(f)));
		}

		bool has(SDL_EventType type) const {
			return handlers.find(static_cast<event_t>(type)) != handlers.end();
		}

		SDL_AppResult operator()(Event e) {
			const auto &type = e.type;
			switch (type) {
				case SDL_EVENT_KEY_DOWN:
					return key.onDown(e.key);
				case SDL_EVENT_KEY_UP:
					return key.onUp(e.key);
				case SDL_EVENT_MOUSE_BUTTON_DOWN:
					return mouse.onDown(e.button);
				case SDL_EVENT_MOUSE_BUTTON_UP:
					return mouse.onUp(e.button);
				default:
					break;
			}
			auto it = handlers.find(type);
			if (it != handlers.end()) {
				return it->second(e);
			}
			return SDL_APP_CONTINUE;
		}

		void clear(SDL_EventType type) {
			handlers.erase(static_cast<event_t>(type));
		}
	};
}