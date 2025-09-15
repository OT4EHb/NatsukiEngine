#include "pch.h"
#include "StartState.hpp"
#include "TabState.hpp"

StartState::StartState() {
	registerKeyDown(
		SDL_SCANCODE_SPACE,
		[](GameSystems *systems, SDL_Event *e) {
			return SDL_APP_SUCCESS;
		});
	registerKeyDown(
		SDL_SCANCODE_TAB,
		[](GameSystems *systems, SDL_Event *e) {
			systems->stateManager.change<TabState>(systems);
			return SDL_APP_CONTINUE;
		}
	);
}

void StartState::update(GameSystems *systems, Uint64 deltaTime) {
	std::cout << SDL_SECONDS_TO_NS(1) / deltaTime << "\n";
}

void StartState::render(GameSystems *systems) {
	const auto ren = systems->rendererManager.get("main");
	ren->clear();
	ren->setDrawColor({255, 0, 0, 255});
	const SDL_FRect f{0, 0, 100, 100};
	ren->fillRect(&f);
	ren->present();
}