export module PositionSize;
export import Position;

export using PositionSize = SDL_FRect;

export template<>
struct traitComponent<PositionSize> :std::true_type {};