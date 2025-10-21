export module Timer;
import <SDL3/SDL_timer.h>;
import <functional>;

inline Uint32 callback(void *timer, Uint32 id, Uint32 interval);

export class Timer {
	using timerCallback = std::function<Uint32(Uint32)>;
	friend Uint32 callback(void *, Uint32, Uint32);
private:
	SDL_TimerID id;
	timerCallback thisCallback;
public:
	inline Timer(Uint32 interval, timerCallback call) {
		id = SDL_AddTimer(interval, callback, static_cast<void *>(this));
		thisCallback = call;
	}

	inline ~Timer() {
		SDL_RemoveTimer(id);
	}
};

inline Uint32 callback(void *timer, Uint32 id, Uint32 interval) {
	return static_cast<Timer *>(timer)->thisCallback(interval);
}