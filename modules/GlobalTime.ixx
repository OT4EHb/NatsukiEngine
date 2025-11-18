export module GlobalTime;
import <SDL3/SDL_timer.h>;

export class GlobalTime {
public:
	GlobalTime() = delete;
	static inline Uint64 getDelta() {
	#ifdef _DEBUG
		auto tmp = getTicks() - time;
		return tmp > 100 ? 10 : tmp;
	#endif
		return getTicks() - time;
	}
	static inline Uint64 update() {
		Uint64 tmp = time;
		time = getTicks();
		return time - tmp;
	}
	static inline Uint64 getDeltaNS() {
	#ifdef _DEBUG
		auto tmp = getTicksNS() - time;
		return tmp > 10000 ? 1000 : tmp;
	#endif
		return getTicksNS() - timeNS;
	}
	static inline Uint64 updateNS() {
		Uint64 tmp = timeNS;
		timeNS = getTicksNS();
		return timeNS - tmp;
	}
	static inline Uint64 getTicks() {
		return SDL_GetTicks();
	}
	static inline Uint64 getTicksNS() {
		return SDL_GetTicksNS();
	}
private:
	static inline Uint64 time{getTicks()};
	static inline Uint64 timeNS{getTicksNS()};
};