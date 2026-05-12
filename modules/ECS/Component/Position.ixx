module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.Position;

export namespace Natsuki {
	struct Position :public SDL_FPoint {};
}