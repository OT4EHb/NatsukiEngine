#pragma once
class Mineswaper;
union SDL_Event;
enum SDL_AppResult;
import Natsuki.Time.DeltaTime;

class MenuState {
private:
	Mineswaper &game;
	float opacity;
	bool direction;
	Natsuki::DeltaTime delta;
public:
	MenuState(Mineswaper &game);
	void enter();
	void exit();
	bool render();
	SDL_AppResult event(SDL_Event &event);
};