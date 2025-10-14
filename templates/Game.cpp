module Game;

SDL_AppResult Game::iterate(Context &context) {

	return SDL_APP_CONTINUE;
}

SDL_AppResult Game::eventHandler(Context &context, SDL_Event *event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}

	return SDL_APP_CONTINUE;
}