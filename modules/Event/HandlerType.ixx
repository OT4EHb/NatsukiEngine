module;
#include <concepts>
#include <functional>
#include <SDL3/SDL_init.h>
export module Natsuki.Event.HandlerType;

export using ::SDL_AppResult;
export using ::SDL_EventType;

export namespace Natsuki {
	template<class F, class Event>
		requires std::invocable<F, Event>
	constexpr decltype(auto) make_handler(F &&f) noexcept(std::is_nothrow_invocable_v<F, Event>) {
		using Handler = std::function<SDL_AppResult(Event)>;
		using Result = std::invoke_result_t<F, Event>;

		if constexpr (std::same_as<Result, SDL_AppResult>) {
			return Handler(std::forward<F>(f));
		}
		else {
			return [h = std::forward<F>(f)](Event e) {
				h(e);
				return SDL_APP_CONTINUE;
			};
		}
	}
}