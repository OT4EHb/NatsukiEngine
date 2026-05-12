module;
#include <SDL3/SDL_rect.h>
export module Natsuki.Math.Rect;
export import Natsuki.Math.Point;

export namespace Natsuki {
	using Rect = SDL_Rect;
	using FRect = SDL_FRect;

	inline bool hasIntersection(const Rect &lft, const Rect &rht) {
		return SDL_HasRectIntersection(&lft, &rht);
	}

	inline bool hasIntersection(const FRect &lft, const FRect &rht) {
		return SDL_HasRectIntersectionFloat(&lft, &rht);
	}
}