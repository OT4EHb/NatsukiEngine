module;
#include <functional>
#include <SDL3/SDL_timer.h>
export module Natsuki.Time.Timer;

export namespace Natsuki {
	class Timer {
		using timerCallback = std::function<Uint32(Uint32)>;
	private:
		SDL_TimerID id;
		timerCallback callback;

		static inline Uint32 callbackLogic(void *timer, Uint32 id, Uint32 interval) {
			return static_cast<Natsuki::Timer *>(timer)->callback(interval);
		}
	public:
		inline Timer(Uint32 interval, timerCallback call) {
			id = SDL_AddTimer(interval, callbackLogic, static_cast<void *>(this));
			callback = call;
		}

		inline ~Timer() {
			stop();
		}

		inline bool stop() {
			return SDL_RemoveTimer(id);
		}

		Timer(const Timer &) = delete;
		Timer &operator=(const Timer &) = delete;

		Timer(Timer &&) = delete;
		Timer &operator=(Timer &&) = delete;
	};
}