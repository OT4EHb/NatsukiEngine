module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.PositionSize;
export import Natsuki.ECS.Component.Position;

export namespace Natsuki {
	struct PositionSize {
		float x;
		float y;
		float w;
		float h;
		inline operator SDL_FRect &() {
			return reinterpret_cast<SDL_FRect &>(*this);
		}
		inline operator Position &() {
			return reinterpret_cast<Position &>(*this);
		}
	};
}