module;
#include <SDL3_ttf/SDL_ttf.h>
module Natsuki.SDL;
import Natsuki.Exception;

using namespace Natsuki;

SDL::SDL(SDL_InitFlags flags) {
	checkCallSDL(SDL_Init(flags));
	checkCallSDL(TTF_Init());
}

SDL::~SDL() {
	TTF_Quit();
	SDL_Quit();
}