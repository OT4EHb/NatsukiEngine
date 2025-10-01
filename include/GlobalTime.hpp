#pragma once
#include <SDL3/SDL_timer.h>

class GlobalTime {
public:
	GlobalTime() = delete;
	static Uint64 getDelta(){
		static Uint64 prev = getTicks();
		Uint64 curr = getTicks();
		Uint64 delta = curr - prev;
		prev = curr;
		return delta;
	}
	static Uint64 getTicks() {
		return SDL_GetTicksNS();
	}
};