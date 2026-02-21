#include <NatsukiMain.hpp>

import Natsuki;
using namespace Natsuki;

class MyGame :public Game<MyGame> {
	// custom field, example:
	// SDL sdl; // if you use a library (required for most classes)
	// Window ...
public:
	MyGame();
	~MyGame();
	SDL_AppResult iterate();
	SDL_AppResult eventHandler(SDL_Event *);
};

SET_GAME(MyGame);

SDL_AppResult Game::iterate() {
	// action within one frame
	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::eventHandler(SDL_Event *event) {
	// window closing handling, optional, works only on the last window
	if (event->type == SDL_EVENT_QUIT) {
		setResult(SDL_APP_SUCCESS);
		return SDL_APP_SUCCESS;
	}
	//handling other events
	return SDL_APP_CONTINUE;
}