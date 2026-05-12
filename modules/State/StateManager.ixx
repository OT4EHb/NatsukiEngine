module;
#include <concepts>
#include <variant>
export module Natsuki.State.StateManager;
import Natsuki.State.Concept;

export namespace Natsuki {
	template<typename...States>
	class StateManager {
	private:
		std::variant<States...> current;

		template<typename T>
		constexpr static void callEnter(T &state) {
			if constexpr (HasEnter<T>) {
				state.enter();
			}
		}

		template<typename T>
		constexpr static void callExit(T &state) {
			if constexpr (HasExit<T>) {
				state.exit();
			}
		}
	public:
		template<typename T>
			requires (std::is_same_v<T, States> || ...)
		constexpr StateManager(T&&startState) :
			current(std::forward<T>(startState)) {

			std::visit([](auto &state) {
				callEnter(state);
			}, current);
		}

		template<typename T>
		constexpr bool is() const {
			return std::holds_alternative<T>(current);
		}
		
		template<typename T, typename... Args>
			requires (std::constructible_from<T, Args...>
		&& (std::is_same_v<T,States>||...))
		constexpr void change(Args&&... args) {
			std::visit([](auto &state) {
				callExit(state);
			}, current);
			current.template emplace<T>(std::forward<Args>(args)...);
			std::visit([](auto &state) {
				callEnter(state);
			}, current);
		}

		template<typename T>
		requires (std::is_same_v<T,States>||...)
		constexpr void changeTo(T &&newState) {
			std::visit([](auto &state) {
				callExit(state);
			}, current);
			current = std::forward<T>(newState);
			std::visit([](auto &state) {
				callEnter(state);
			}, current);
		}

		template<typename Visitor>
		constexpr decltype(auto) visit(Visitor &&visitor) {
			return std::visit(std::forward<Visitor>(visitor), current);
		}
	};
}