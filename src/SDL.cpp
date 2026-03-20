module;
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
module Natsuki.SDL;
import Natsuki.Exception;

using namespace Natsuki;

SDL::SDL(SDL_InitFlags flags) {
	checkCallSDL(SDL_Init(flags));
	checkCallSDL(TTF_Init());
	checkCallSDL(MIX_Init());
}

SDL::~SDL() {
	MIX_Quit();
	TTF_Quit();
	SDL_Quit();
}