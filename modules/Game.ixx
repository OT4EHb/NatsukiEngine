export module Game;
import <SDL3/SDL_init.h>;

export class Game {
private:
	static SDL_AppResult result;
public:
	Game() = delete;
	static inline SDL_AppResult getResult();
	static inline void setResult(SDL_AppResult result);
	static void iterate();
	static void eventHandler(SDL_Event *);
};

inline SDL_AppResult Game::getResult() {
	return result;
}

inline void Game::setResult(SDL_AppResult res) {
	result = res;
}