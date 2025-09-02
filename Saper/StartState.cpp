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
		SDL_SCANCODE_LEFT,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.x -= 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_RIGHT,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.x += 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_UP,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.y -= 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_DOWN,
		[](GameSystems *systems, SDL_Event *e) {
			systems->rect.y += 100;
			return SDL_APP_CONTINUE;
		}
	);
	registerKeyDown(
		SDL_SCANCODE_TAB,
		[](GameSystems *systems, SDL_Event *e) {
			systems->changeState(TabState::get());
			return SDL_APP_CONTINUE;
		}
	);
}

StartState *StartState::get() {
	return &instance;
}

void StartState::update(GameSystems *systems, Uint64 deltaTime) {
	std::cout << SDL_SECONDS_TO_NS(1) / deltaTime << "\n";
}

void StartState::render(GameSystems *systems) {
	const Renderer &ren = systems->renderer;
	ren.clear();
	ren.setDrawColor({255, 0, 0, 255});
	ren.fillRect(&systems->rect);
	ren.present();
}

StartState StartState::instance{};