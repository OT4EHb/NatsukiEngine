module;
#include <functional>
#include <SDL3/SDL_timer.h>
export module Natsuki.Time.Timer;
export import Natsuki.Exception;

export using ::Uint32;

export namespace Natsuki {
	class Timer {
	public:
		using timerCallback = std::function<Uint32(Uint32)>;
	private:
		SDL_TimerID id;
		timerCallback callback;

		static inline Uint32 callbackLogic(void *timer, Uint32 id, Uint32 interval) {
			return static_cast<Natsuki::Timer *>(timer)->callback(interval);
		}

		struct IntervalData {
			SDL_TimerID id;
			std::function<void()>callback;
		};
		static Uint32 intervalLogic(void *intervaldata, Uint32 id, Uint32 interval) {
			auto *data = static_cast<IntervalData *>(intervaldata);
			data->callback();
			SDL_RemoveTimer(data->id);
			delete data;
			return 0;
		}
	public:
		inline Timer(Uint32 interval, timerCallback call) {
			id = SDL_AddTimer(interval, callbackLogic, static_cast<void *>(this));
			checkCall(id != 0);
			callback = call;
		}
		inline ~Timer() {
			stop();
		}

		inline bool stop() {
			if (id == 0) return false;
			bool result= SDL_RemoveTimer(id);
			id = 0;
			return result;

		}

		Timer(const Timer &) = delete;
		Timer &operator=(const Timer &) = delete;

		Timer(Timer &&) = delete;
		Timer &operator=(Timer &&) = delete;

		static bool setInterval(Uint32 delay, std::function<void()> callback) {
			
			auto *data = new IntervalData(0, std::move(callback));
			data->id = SDL_AddTimer(delay, intervalLogic, data);
			if (data->id == 0) {
				delete data;
				return false;
			}
			return true;
		}
	};
}