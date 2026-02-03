module;
#include <SDL3/SDL_timer.h>
export module Natsuki.Time.GlobalTime;

export namespace Natsuki {
	using time_type = Uint64;
	
	constexpr time_type MS_PER_SECOND = SDL_MS_PER_SECOND;
	constexpr time_type US_PER_SECOND = SDL_US_PER_SECOND;
	constexpr time_type NS_PER_SECOND = SDL_NS_PER_SECOND;
	constexpr time_type NS_PER_MS = SDL_NS_PER_MS;
	constexpr time_type NS_PER_US = SDL_NS_PER_US;

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