module;
#include <cmath>
#include <SDL3/SDL_rect.h>
export module Natsuki.Math.Point;

export namespace Natsuki {
	using Point = SDL_Point;
	using FPoint = SDL_FPoint;

	inline float get_norm(const FPoint&p) {
		return std::sqrt(std::powf(p.x, 2) + std::powf(p.y, 2));
	}

	inline void normalize(FPoint &p, float eps) {
		float norm = get_norm(p);
		if (norm > eps) {
			p.x /= norm;
			p.y /= norm;
		}
	}

	inline float scalar(const FPoint &lft, const FPoint &rht) {
		return lft.x * rht.x + lft.y * rht.y;
	}
}