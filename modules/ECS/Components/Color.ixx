export module Color;
import <SDL3/SDL_pixels.h>;

export struct Color {
	using componentTag = void;
	SDL_Color color;
	inline SDL_Color &asSDL() {
		return color;
	}
};