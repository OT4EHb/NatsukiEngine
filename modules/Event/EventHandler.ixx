module;
#include <array>
#include <concepts>
#include <functional>
#include <unordered_map>
#include <SDL3/SDL_init.h>
export module Natsuki.Event.EventHandler;

export using ::SDL_EventType;

export namespace Natsuki {
	class EventHandler {
	private:
		static inline constexpr auto LAST_EVENT = SDL_EVENT_CLIPBOARD_UPDATE;
		using event_t = Uint32;
		using handler_type = std::function<SDL_AppResult(SDL_Event *)>;
		std::array<handler_type, LAST_EVENT + 1 > freq;
		std::unordered_map<event_t, handler_type> rare;

		void set_impl(event_t type, handler_type f) {
			if (isFrequent(type)) {
				freq[type] = std::move(f);
			}
			else {
				rare[type] = std::move(f);
			}
		}
	public:
		static constexpr inline bool isFrequent(event_t type) noexcept{
			return type <= LAST_EVENT;
		}

		template<class F>
		requires std::invocable<F, SDL_Event*>
		void set(event_t type, F &&f) {
			if constexpr (std::is_same_v<std::invoke_result_t<F, SDL_Event *>, SDL_AppResult>) {
				set_impl(type, std::forward<F>(f));
			}
			else {
				set_impl(type, [h = std::forward<F>(f)](SDL_Event *e) {
					h(e);
					return SDL_APP_CONTINUE;
				});
			}
		}

		bool has(event_t type) const {
			if (isFrequent(type)) {
				return static_cast<bool>(freq[type]);
			}
			return rare.find(type) != rare.end();
		}

		SDL_AppResult operator()(SDL_Event *e) {
			auto &type = e->type;
			if (isFrequent(type)) {
				auto &h = freq[type];
				if (h) {
					return h(e);
				}
			}
			else {
				auto it = rare.find(type);
				if (it != rare.end()) {
					return it->second(e);
				}
			}
			return SDL_APP_CONTINUE;
		}

		void clear(event_t type) {
			if (isFrequent(type)) {
				freq[type] = nullptr;
			}
			else {
				rare.erase(type);
			}
		}
	};
}