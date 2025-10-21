export module Handler;
import <functional>;
import <unordered_map>;
import <SDL3/SDL_init.h>;
export class Handler {
protected:
	using EventHandler = std::function<void(SDL_Event *)>;
	std::unordered_map<SDL_EventType, EventHandler> eventHandlers;
public:
	inline void registerHandler(SDL_EventType type, EventHandler handler) {
		eventHandlers[type] = handler;
	}
};