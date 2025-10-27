module Game;
import Context;

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