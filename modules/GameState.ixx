export module GameState;
import Handler;

export class GameState :public Handler {
public:
	virtual SDL_AppResult eventHandler(Context &context, SDL_Event *event) const {
		auto it = eventHandlers.find(static_cast<SDL_EventType>(event->type));
		if (it != eventHandlers.end()) {
			return it->second(context, event);
		}
		return SDL_APP_CONTINUE;
	}
	virtual void enter(Context &) {};
	virtual void exit(Context &) {};
	virtual SDL_AppResult iterate(Context &) = 0;
	virtual ~GameState() = default;
};