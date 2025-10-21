module Game;
import Context;

SDL_AppResult Game::result{SDL_APP_CONTINUE};

void Game::iterate() {
	//
}

void Game::eventHandler(SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		setResult(SDL_APP_SUCCESS);
		return;
	}
	//
}