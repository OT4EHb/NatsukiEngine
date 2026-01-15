module;
#include <SDL3/SDL_timer.h>
export module Natsuki.Time.GlobalTime;


export namespace Natsuki {
	using time_type = Uint64;

	class GlobalTime {
	public:
		GlobalTime() = delete;
		static inline time_type getTicks() {
			return SDL_GetTicks();
		}
		static inline time_type getTicksNS() {
			return SDL_GetTicksNS();
		}
	};
}