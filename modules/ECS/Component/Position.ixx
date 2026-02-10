module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.Position;
export import Natsuki.ECS.BaseComponent;

export namespace Natsuki {
	struct Position {
		SDL_FPoint point{};
		constexpr inline operator SDL_FPoint &() {
			return point;
		}
	};
}