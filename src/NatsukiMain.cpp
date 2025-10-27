#pragma comment(lib,"SDL3.lib")
#pragma comment(lib,"SDL3_ttf.lib")
#pragma comment(lib,"SDL3_image.lib")

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

import <string>;
import SDL;
import SDLException;
import Game;
import MessageBox;

static void errorCallback(std::string_view error) {
	MessageBox()
		.setTitle("Error SDL")
		.setFlag(MessageBoxFlags::ERROR)
		.setMessage(error)
		.show();
}

static SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	if (!SDL::init()) {
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	try {
		Game::iterate();
	}
	catch (SDLException&e) {
		Game::setResult(SDL_APP_FAILURE);
		errorCallback(e.what());
	}
	return Game::getResult();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	try {
		Game::eventHandler(event);
	}
	catch (SDLException&e) {
		Game::setResult(SDL_APP_FAILURE);
		errorCallback(e.what());
	}
	return Game::getResult();
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	SDL::quit();
}