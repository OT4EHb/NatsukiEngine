export module GlobalTime;
import <SDL3/SDL_timer.h>;

export class GlobalTime {
public:
	GlobalTime() = delete;
	static Uint64 getDelta(){
		static Uint64 prev = getTicks();
		Uint64 curr = getTicks();
		Uint64 delta = curr - prev;
		prev = curr;
		return delta;
	}
	static Uint64 getDeltaNS() {
		static Uint64 prev = getTicksNS();
		Uint64 curr = getTicksNS();
		Uint64 delta = curr - prev;
		prev = curr;
		return delta;
	}
	inline static Uint64 getTicks() {
		return SDL_GetTicks();
	}
	inline static Uint64 getTicksNS() {
		return SDL_GetTicksNS();
	}
};