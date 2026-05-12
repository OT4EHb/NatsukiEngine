#include <MenuState.hpp>
#include <Game.hpp>

MenuState::MenuState(Mineswaper &game) :game(game),
opacity(1.f),direction(1) {}

void MenuState::enter() {
	game.renderer.setScale({4.f, 4.f});
}

void MenuState::exit() {
	game.renderer.setScale({1.f, 1.f});
}

bool MenuState::render() {
	//random
	constexpr float coof = 1.f / 1000.f;
	auto dt = delta.update();
	if (direction) {
		opacity -= dt * coof;
		if (opacity <= 0.2f) direction = 0;
	}
	else {
		opacity += dt * coof;
		if (opacity >= 0.99f) direction = 1;
	}
	auto &ren = game.renderer;
	ren.setDrawColor(SDL_Color(255, 0, 0, opacity*255.f));
	ren.renderDebugText("Any key to start", {38, 95});
	//end random
	return true;
}

SDL_AppResult MenuState::event(SDL_Event &e) {
	switch (e.type) {
		case SDL_EVENT_KEY_DOWN:
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			game.stater.change<GameState>(game);
		default:
			break;
	}
	return SDL_APP_CONTINUE;
}
