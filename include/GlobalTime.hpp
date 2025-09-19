#pragma once
#include <SDL3/SDL_timer.h>
#include <SDL3/SDL_init.h>
class GlobalTime {
	friend SDL_AppResult SDL_AppIterate(void *);
private:
	static Uint64 getDelta(){
		static Uint64 prev = getTicks();
		Uint64 curr = getTicks();
		Uint64 delta = curr - prev;
		prev = curr;
		return delta;
	}
public:
	GlobalTime() = delete;
	static Uint64 getTicks() {
		return SDL_GetTicksNS();
	}
};