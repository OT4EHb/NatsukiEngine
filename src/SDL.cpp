module;
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
module Natsuki.SDL;
import Natsuki.Exception;

using namespace Natsuki;

SDL::SDL(Flags flags) {
	checkCall(SDL_Init(static_cast<SDL_InitFlags>(flags)));
	checkCall(TTF_Init());
	checkCall(MIX_Init());
}

SDL::~SDL() {
	MIX_Quit();
	TTF_Quit();
	SDL_Quit();
}