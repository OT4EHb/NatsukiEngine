#pragma comment(lib,"SDL3.lib")
#pragma comment(lib,"SDL3_ttf.lib")
#pragma comment(lib,"SDL3_image.lib")

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
//#include <SDL3/SDL.h>

import SDL;
import Game;

static SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	if (!SDL::init()) {
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	Game::iterate();
	return Game::getResult();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	Game::eventHandler(event);
	return Game::getResult();
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	if (result == SDL_APP_FAILURE) {
		//SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
	}
	SDL::quit();
}