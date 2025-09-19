#include "Saper.hpp"
#define GAME Saper
#include <NatsukiMain.hpp>

Saper::Saper():window("Main",500,500) {

}

Saper::~Saper() {

}

SDL_AppResult Saper::iterate() {
	return SDL_APP_CONTINUE;
}

SDL_AppResult Saper::eventHandler(SDL_Event*event) {
	if (event->type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return SDL_APP_CONTINUE;
}