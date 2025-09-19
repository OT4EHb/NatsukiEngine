#pragma comment(lib,"SDL3.lib")
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <Game.hpp>
#include <SDL.hpp>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	SDL::init();
	Game *game = new GAME();
	*appstate = static_cast<void *>(game);
	return SDL_APP_CONTINUE;
}

inline SDL_AppResult SDL_AppIterate(void *appstate) {
	Game *game = static_cast<Game *>(appstate);
	return game->iterate();
}

inline SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	Game *game = static_cast<Game *>(appstate);
	return game->eventHandler(event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	Game *game = static_cast<Game *>(appstate);
	delete game;
	if (result == SDL_APP_FAILURE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
	}
}