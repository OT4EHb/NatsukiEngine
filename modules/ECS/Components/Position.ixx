module;
#include <SDL3/SDL_rect.h>
export module Position;
export import Component;

export SDL_FRect;

export using Position = SDL_FPoint;

export template<>
struct traitComponent<Position> :std::true_type {};