#pragma comment(lib,"Natsuki.lib")
#pragma comment(lib,"SDL3.lib")

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <Game.hpp>
#include <SDL.hpp>

#ifndef INIT_FLAGS
#define INIT_FLAGS SDL_INIT_VIDEO
#endif // !INIT_FLAGS

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	if (!SDL::init(INIT_FLAGS)) {
		return SDL_APP_FAILURE;
	}
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
	delete static_cast<Game *>(appstate);
	if (result == SDL_APP_FAILURE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
	}
	SDL::quit();
}