module;
#include <array>
#include <concepts>
#include <functional>
#include <SDL3/SDL_init.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
export module Natsuki.Event.MouseSystem;

export using ::SDL_AppResult;
export using ::SDL_MouseButtonEvent;

export namespace Natsuki {
	class MouseSystem {
	public:
		enum class Button :SDL_MouseButtonFlags {
			LEFT = SDL_BUTTON_LEFT,
			MIDDLE = SDL_BUTTON_MIDDLE,
			RIGHT = SDL_BUTTON_RIGHT,
			X1 = SDL_BUTTON_X1,
			X2 = SDL_BUTTON_X2
		};
	private:
		using SIZE_T = Uint8;
		static constexpr SIZE_T SIZE = 5;
		using Event = SDL_MouseButtonEvent &;
		using handler_type = std::function<SDL_AppResult(Event)>;
		std::array<handler_type, SIZE> mouseDown;
		std::array<handler_type, SIZE> mouseUp;
	public:
		template<class F>
			requires std::invocable<F, Event>
		void setDown(Button button, F &&f) {
			mouseDown[static_cast<SIZE_T>(button)] = std::forward<handler_type>(make_handler<F, Event>(std::forward<F>(f)));
		}

		template<class F>
			requires std::invocable<F, Event>
		void setUp(Button button, F &&f) {
			mouseUp[static_cast<SIZE_T>(button)] = std::forward<handler_type>(make_handler<F, Event>(std::forward<F>(f)));
		}

		SDL_AppResult onDown(Event e) {
			auto &h = mouseDown[e.button];
			if (h) {
				return h(e);
			}
			return SDL_APP_CONTINUE;
		}

		SDL_AppResult onUp(Event e) {
			auto &h = mouseUp[e.button];
			if (h) {
				return h(e);
			}
			return SDL_APP_CONTINUE;
		}

		void clearDown(Button button) {
			mouseDown[static_cast<SIZE_T>(button)] = nullptr;
		}

		void clearUp(Button button) {
			mouseUp[static_cast<SIZE_T>(button)] = nullptr;
		}
	};
}