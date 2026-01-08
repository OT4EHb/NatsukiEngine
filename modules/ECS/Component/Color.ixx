module;
#include <SDL3/SDL_pixels.h>
export module Natsuki.ECS.Component.Color;
export import Natsuki.ECS.BaseComponent;

export namespace Natsuki {
	using Color = SDL_Color;

	bool operator==(const Color &left, const Color &right) {
		return left.r == right.r
			&& left.g == right.g
			&& left.b == right.b
			&& left.a == right.a;
	}

	bool operator!=(const Color &left, const Color &right) {
		return !(left == right);
	}
}