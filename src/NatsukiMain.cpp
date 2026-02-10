#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <string>
#include <stdexcept>

import Natsuki.SDL;
import Natsuki.Exception;
import Game;
import Natsuki.MessageBox;

using namespace Natsuki;

static void errorCallback(std::string_view title, std::string_view error) {
	Game::setResult(SDL_APP_FAILURE);
	MessageBox()
		.setTitle(title)
		.setFlag(MessageBox::Flags::ERROR)
		.setMessage(error)
		.show();
}

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	if (!SDL::init()) {
		return SDL_APP_FAILURE;
	}
	Game::init();
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	try {
		Game::iterate();
	}
	catch (const std::runtime_error &e) {
		errorCallback("Runtime Error", e.what());
	}
	return Game::getResult();
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	try {
		Game::eventHandler(event);
	}
	catch (const std::runtime_error &e) {
		errorCallback("Runtime Error", e.what());
	}
	return Game::getResult();
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	SDL::quit();
}