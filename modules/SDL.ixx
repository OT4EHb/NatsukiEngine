module;
#include <string_view>
#include <SDL3/SDL_init.h>
export module Natsuki.SDL;

export namespace Natsuki {
	class SDL {
	public:
		enum class Flags :SDL_InitFlags {
			AUDIO = SDL_INIT_AUDIO,
			VIDEO = SDL_INIT_VIDEO,
			JOYSTICK = SDL_INIT_JOYSTICK,
			HAPTIC = SDL_INIT_HAPTIC,
			GAMEPAD = SDL_INIT_GAMEPAD,
			EVENTS = SDL_INIT_EVENTS,
			SENSOR = SDL_INIT_SENSOR,
			CAMERA = SDL_INIT_CAMERA
		};
	public:
		SDL(Flags = Flags::VIDEO);
		~SDL();
		static inline const char *getError() noexcept {
			return SDL_GetError();
		}
		static inline bool setError(std::string_view error) {
			return SDL_SetError(error.data());
		}
	};
}