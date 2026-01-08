module;
#include <SDL3/SDL_timer.h>
export module Natsuki.Time.GlobalTime;

export Uint64;

export namespace Natsuki {
	class GlobalTime {
	public:
		GlobalTime() = delete;
		static inline Uint64 getTicks() {
			return SDL_GetTicks();
		}
		static inline Uint64 getTicksNS() {
			return SDL_GetTicksNS();
		}
	};
}