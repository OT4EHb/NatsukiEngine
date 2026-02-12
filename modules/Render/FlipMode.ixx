module;
#include <SDL3/SDL_surface.h>
export module Natsuki.Render.FlipMode;

export namespace Natsuki {
	using FlipMode = SDL_FlipMode;
	namespace Flip {
		constexpr auto NONE = SDL_FLIP_NONE;
		constexpr auto HORIZONTAL = SDL_FLIP_HORIZONTAL;
		constexpr auto VERTICAL = SDL_FLIP_VERTICAL;
	}
}