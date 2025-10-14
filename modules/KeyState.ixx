export module KeyState;
import <initializer_list>;
import GameState;

export class KeyState :
	public GameState {
protected:
	std::unordered_map<SDL_Scancode, EventHandler> keyDownHandlers;
	std::unordered_map<SDL_Scancode, EventHandler> keyUpHandlers;
public:
	inline void registerKeyDown(SDL_Scancode type, EventHandler handler) {
		keyDownHandlers[type] = handler;
	}
	void registerKeyDown(std::initializer_list<SDL_Scancode> types, EventHandler handler) {
		for (SDL_Scancode type : types)
			registerKeyDown(type, handler);
	}
	inline void registerKeyUp(SDL_Scancode type, EventHandler handler) {
		keyUpHandlers[type] = handler;
	}
	void registerKeyUp(std::initializer_list<SDL_Scancode> types, EventHandler handler) {
		for (SDL_Scancode type : types)
			registerKeyUp(type, handler);
	}
	SDL_AppResult eventHandler(Context &context, SDL_Event *event) const override {
		if (event->type == SDL_EVENT_KEY_UP) {
			auto it = keyUpHandlers.find(static_cast<SDL_Scancode>(event->key.scancode));
			if (it != keyUpHandlers.end()) {
				return it->second(context, event);
			}
			return SDL_APP_CONTINUE;
		}
		if (event->type == SDL_EVENT_KEY_DOWN) {
			auto it = keyDownHandlers.find(static_cast<SDL_Scancode>(event->key.scancode));
			if (it != keyDownHandlers.end()) {
				return it->second(context, event);
			}
			return SDL_APP_CONTINUE;
		}
		return GameState::eventHandler(context, event);
	}
};