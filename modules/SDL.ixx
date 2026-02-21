module;
#include <SDL3/SDL_init.h>
export module Natsuki.SDL;

export namespace Natsuki {
	class SDL {
	public:
		SDL(SDL_InitFlags = SDL_INIT_VIDEO);
		~SDL();
		static inline const char *getError() noexcept;
	};
}

const char *Natsuki::SDL::getError() noexcept {
	return SDL_GetError();
}