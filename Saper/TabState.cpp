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
		SDL_SCANCODE_TAB,
		[](GameSystems *systems, SDL_Event *e) {
			systems->stateManager.change<StartState>(systems);
			return SDL_APP_CONTINUE;
		}
	);
}

void TabState::update(GameSystems *systems, Uint64 deltaTime) {
	std::cout << SDL_SECONDS_TO_NS(1) / deltaTime << "\n";
}

void TabState::render(GameSystems *systems) {
	const auto ren = systems->rendererManager.get("main");
	ren->clear();
	ren->setDrawColor({255, 0, 0, 255});
	const SDL_FRect f{0, 0, 100, 100};
	ren->rect(&f);
	ren->present();
}