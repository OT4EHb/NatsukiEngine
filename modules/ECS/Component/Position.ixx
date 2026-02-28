module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.Position;

export namespace Natsuki {
	struct Position {
		float x;
		float y;
		inline operator SDL_FPoint &() {
			return reinterpret_cast<SDL_FPoint &>(*this);
		}
	};
}