module SDL;
import <SDL3_ttf/SDL_ttf.h>;

bool SDL::init(SDL_InitFlags flags) {
	return SDL_Init(flags) &&
		TTF_Init();
}

void SDL::quit() noexcept {
	TTF_Quit();
	SDL_Quit();
}