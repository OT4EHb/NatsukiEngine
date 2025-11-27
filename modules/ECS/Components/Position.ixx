export module Position;
export import <SDL3/SDL_rect.h>;
export import Component;

export using Position = SDL_FPoint;

export template<>
struct traitComponent<Position> :std::true_type {};