#include <NatsukiMain.hpp>
#include <functional>
#include <Game.hpp>

SET_GAME(Mineswaper);

template <class T>
concept MainState = requires (T state, SDL_Event&e) {
	{ state.render() }->std::same_as<bool>;
	{ state.event(e) }->std::same_as<SDL_AppResult>;
};

struct VisitRender {
	bool operator()(MainState auto &state) {
		return state.render();
	}
};

SDL_AppResult Mineswaper::iterate() {
	Natsuki::RendererGuard guard(renderer);
	stater.visit(VisitRender{});
	return SDL_APP_CONTINUE;
}

SDL_AppResult Mineswaper::eventHandler(SDL_Event &event) {
	if (event.type == SDL_EVENT_QUIT) {
		return SDL_APP_SUCCESS;
	}
	return stater.visit([&event](MainState auto &state) {
		return state.event(event);
	});
}