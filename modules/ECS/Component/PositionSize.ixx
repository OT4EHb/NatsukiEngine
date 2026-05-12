module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.PositionSize;
export import Natsuki.ECS.Component.Position;

export namespace Natsuki {
	struct PositionSize:public SDL_FRect {
		inline operator Position &() {
			return reinterpret_cast<Position &>(*this);
		}
	};
}