export module GameState;
import Handler;

export class GameState :public Handler {
public:
	virtual void eventHandler(SDL_Event *event) const {
		auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
		if (it != eventHandlers.end()) {
			it->second(event);
		}
	}
	virtual void enter() {};
	virtual void exit() {};
	virtual void iterate() = 0;
	virtual ~GameState() = default;
};