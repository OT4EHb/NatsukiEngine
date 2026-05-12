#pragma once
#include <MenuState.hpp>
#include <GameState.hpp>
import Natsuki;

class Mineswaper :public Natsuki::Game<Mineswaper> {
public:
	Natsuki::SDL sdl{Natsuki::SDL::Flags::VIDEO};
	Natsuki::Window window{"Mineswaper", 800, 800};
	Natsuki::Renderer renderer{window};
	Natsuki::EventHandler eventler;
	Natsuki::StateManager<MenuState, ::GameState> stater{MenuState{*this}};
public:
	SDL_AppResult iterate();
	SDL_AppResult eventHandler(SDL_Event &);
	static void setMetadata() {
		Natsuki::Metadata::setAppName("Mineswaper");
	}
};