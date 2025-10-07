#pragma comment(lib,"SDL3.lib")
#pragma comment(lib,"SDL3_ttf.lib")
#pragma comment(lib,"SDL3_image.lib")

#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>

#include <Game.hpp>
#include <SDL.hpp>
#include "Context.hpp"

#ifndef INIT_FLAGS
#define INIT_FLAGS SDL_INIT_VIDEO
#endif // !INIT_FLAGS

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	if (!SDL::init(INIT_FLAGS)) {
		return SDL_APP_FAILURE;
	}
	Context *context = new Context();
	*appstate = static_cast<void *>(context);
	return SDL_APP_CONTINUE;
}

inline SDL_AppResult SDL_AppIterate(void *appstate) {
	Context *context = static_cast<Context *>(appstate);
	return Game::iterate(*context);
}

inline SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	Context *context = static_cast<Context *>(appstate);
	return Game::eventHandler(*context,event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	if (result == SDL_APP_FAILURE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
	}
	delete static_cast<Context *>(appstate);
	SDL::quit();
}