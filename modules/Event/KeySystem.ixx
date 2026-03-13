module;
#include <array>
#include <concepts>
#include <functional>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
export module Natsuki.Event.KeySystem;
export import Natsuki.Event.HandlerType;

export using ::SDL_AppResult;
export using ::SDL_Scancode;
export using ::SDL_KeyboardEvent;

export namespace Natsuki {
	class KeySystem {
	private:
		static constexpr auto SIZE = SDL_SCANCODE_COUNT;
		using Event = SDL_KeyboardEvent &;
		using handler_type = std::function<SDL_AppResult(Event)>;
		std::array<handler_type, SIZE> keyDown;
		std::array<handler_type, SIZE> keyUp;
	public:
		template<class F>
			requires std::invocable<F, Event>
		void setDown(SDL_Scancode scan, F &&f) {
			keyDown[scan] = std::forward<handler_type>(make_handler<F,Event>(std::forward<F>(f)));
		}

		template<class F>
			requires std::invocable<F, Event>
		void setUp(SDL_Scancode scan, F &&f) {
			keyUp[scan] = std::forward<handler_type>(make_handler<F, Event>(std::forward<F>(f)));
		}

		SDL_AppResult onDown(Event e) {
			auto &h = keyDown[e.scancode];
			if (h) {
				return h(e);
			}
			return SDL_APP_CONTINUE;
		}

		SDL_AppResult onUp(Event e) {
			auto &h = keyUp[e.scancode];
			if (h) {
				return h(e);
			}
			return SDL_APP_CONTINUE;
		}

		void clearDown(SDL_Scancode scan) {
			keyDown[scan] = nullptr;
		}

		void clearUp(SDL_Scancode scan) {
			keyUp[scan] = nullptr;
		}
	};
}