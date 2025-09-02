#include "pch.h"
#include "TabState.hpp"
#include "StartState.hpp"

TabState::TabState() {
	registerHandler(
		SDL_EVENT_QUIT,
		[](GameSystems *systems, SDL_Event *e) {
			return SDL_APP_SUCCESS; }
	);
	registerKeyDown(
		SDL_SCANCODE_A,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.x -= 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_D,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.x += 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_W,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.y -= 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_S,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.y += 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_TAB,
		[](GameSystems *systems, SDL_Event *e) {
			systems->changeState(StartState::get());
			return SDL_APP_CONTINUE;
		}
	);
}
TabState *TabState::get() {
	return &instance;
}
void TabState::update(GameSystems *systems, Uint64 deltaTime) {
	std::cout << SDL_SECONDS_TO_NS(1) / deltaTime << "\n";
}
void TabState::render(GameSystems *systems) {
	const Renderer &ren = systems->renderer;
	ren.clear();
	ren.setDrawColor({255, 0, 0, 255});
	ren.rect(&systems->rect);
	ren.present();
}

TabState TabState::instance{};