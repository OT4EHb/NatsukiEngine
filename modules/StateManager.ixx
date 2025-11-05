export module StateManager;
import <typeindex>;
import <unordered_map>;
import <type_traits>;
export import GameState;

template<typename T>
concept GameStateType = std::is_base_of_v<GameState, T>;

export class StateManager {
private:
	std::unordered_map<std::type_index, GameState*> states;
	GameState* current;
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

	template<GameStateType T>
	bool release() {
		std::type_index type = typeid(T);
		if (auto it = states.find(type); it != states.end() && current != *it) {
			delete *it;
			states.erase(it);
			return true;
		}
		return false;
	}

	GameState* getCurrent() const {
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