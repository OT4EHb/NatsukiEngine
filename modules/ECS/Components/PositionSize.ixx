export module PositionSize;
import <SDL3/SDL_rect.h>;
export import Position;
export import Size;

export struct PositionSize :public Position, public Size {	
	using componentTag = void;
	inline SDL_FRect &asSDL() {
		return reinterpret_cast<SDL_FRect &>(*this);
	}
};