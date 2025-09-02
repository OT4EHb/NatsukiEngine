#pragma comment(lib,"SDL3.lib")
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <GameSystems.hpp>
#include <SDL.hpp>
#include <GameDll.hpp>

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
	SDL::init();
	GameSystems *systems = GameSystems::get();
	systems->currentState = (GameDll::init("Saper.dll"));
	if (!systems->isValidState()) {
		SDL_SetError("Invalid DLL");
		return SDL_APP_FAILURE;
	}
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
	auto *systems = GameSystems::get();
	GameState *curr = systems->currentState;
	curr->update(systems, GlobalTime::getDelta());
	curr->render(systems);
	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
	auto *systems = GameSystems::get();
	return systems->currentState->eventHandler(systems, event);
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
	if (result == SDL_APP_FAILURE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), nullptr);
	}
}