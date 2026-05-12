#pragma once
import Area;
class Mineswaper;
union SDL_Event;
enum SDL_AppResult;

class GameState {
private:
	Mineswaper &game;
	Area area;

	void checkResult(Result result);
public:
	GameState(Mineswaper &game);
	void enter();
	void exit();
	bool render();
	SDL_AppResult event(SDL_Event &event);
};