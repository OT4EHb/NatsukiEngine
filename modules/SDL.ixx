module;
#include <SDL3/SDL_init.h>
export module Natsuki.SDL;

export namespace Natsuki {
	class SDL {
	public:
		SDL() = delete;
		static bool init(SDL_InitFlags flags = SDL_INIT_VIDEO);
		static void quit() noexcept;
		static inline const char *getError() noexcept;
	};
}

using namespace Natsuki;

const char *SDL::getError() noexcept {
	return SDL_GetError();
}