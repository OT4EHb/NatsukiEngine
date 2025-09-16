#pragma once
#include <typeindex>
#include <unordered_map>
#include <type_traits>
#include <GameState.hpp>

template<typename T>
concept GameStateType = std::is_base_of_v<GameState, T>;

class StateManager {
private:
	std::unordered_map<std::type_index, GameState*> states;
	GameState *current;
public:
	StateManager() :current(nullptr) {}
	~StateManager() = default;

	template<GameStateType T, typename... Args>
	void addState(Args&&... args) {
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

	const GameState *getCurrent() const {
		return current;
	}

	template<GameStateType T>
	bool change(GameSystems *systems) {
		if (auto state = get<T>()) {
			if (current) {
				current->exit(systems);
			}
			current = state;
			current->enter(systems);
			return true;
		}
		return false;
	}
};