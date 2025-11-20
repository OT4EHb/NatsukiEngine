export module GlobalTime;
import <SDL3/SDL_timer.h>;
export Uint64;

export class GlobalTime {
public:
	GlobalTime() = delete;
	static inline Uint64 getTicks() {
		return SDL_GetTicks();
	}
	static inline Uint64 getTicksNS() {
		return SDL_GetTicksNS();
	}
};