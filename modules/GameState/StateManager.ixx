module;
#include <typeindex>
#include <unordered_map>
#include <type_traits>
export module Natsuki.GameState.StateManager;
export import Natsuki.GameState.BaseGameState;

template<typename T>
concept GameStateType = std::derived_from<T, Natsuki::BaseGameState>;

export namespace Natsuki {
	class StateManager {
	private:
		std::unordered_map<std::type_index, GameState *> states;
		GameState *current;
	public:
		StateManager() :current(nullptr) {}
		~StateManager() {
			for (auto &i : states) {
				delete i.second;
			}
		}

		template<GameStateType T, typename... Args>
			requires std::constructible_from<T, Args...>
		void addState(Args&&... args) {
			if (get<T>()) return;
			std::type_index type = typeid(T);
			states[type] = new T(std::forward<Args>(args)...);
		}

		template<GameStateType T>
		T *get() const {
			std::type_index type = typeid(T);
			if (auto it = states.find(type); it != states.end()) {
				return static_cast<T *>(it->second);
			}
			return nullptr;
		}

		template<GameStateType T>
		bool release() {
			std::type_index type = typeid(T);
			if (auto it = states.find(type); it != states.end() && current != *it) {
				delete it->second;
				states.erase(it);
				return true;
			}
			return false;
		}

		GameState *getCurrent() const {
			return current;
		}

		template<GameStateType T>
		bool change() {
			if (auto state = get<T>()) {
				if (current) {
					current->exit();
				}
				current = state;
				current->enter();
				return true;
			}
			return false;
		}
	};
}