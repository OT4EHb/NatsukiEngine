module;
class Context;
export module Game;
import <SDL3/SDL_init.h>;

export class Game {
public:
	Game() = delete;
	static SDL_AppResult iterate(Context&);
	static SDL_AppResult eventHandler(Context&,SDL_Event *);
};