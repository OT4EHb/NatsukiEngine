module;
#include <SDL3/SDL_rect.h>
export module Natsuki.ECS.Component.Position;
export import Natsuki.ECS.BaseComponent;

export namespace Natsuki {
	using Position = SDL_FPoint;
}