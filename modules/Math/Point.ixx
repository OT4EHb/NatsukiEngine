module;
#include <SDL3/SDL_rect.h>
export module Natsuki.Math.Point;

export namespace Natsuki {
	using Point = SDL_Point;
	using FPoint = SDL_FPoint;
}