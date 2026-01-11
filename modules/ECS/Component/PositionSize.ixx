module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.PositionSize;
export import Natsuki.ECS.BaseComponent;

export namespace Natsuki {
	using PositionSize = SDL_FRect;
}