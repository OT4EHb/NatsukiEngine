export module Color;
import <SDL3/SDL_pixels.h>;

export struct Color {
	using componentTag = void;
	SDL_Color color;
	inline SDL_Color &asSDL() {
		return color;
	}
	bool operator==(const Color &other) const {
		return color.r == other.color.r
			&& color.g == other.color.g
			&& color.b == other.color.b
			&& color.a == other.color.a;
	}
	bool operator!=(const Color &other) const {
		return !(*this == other);
	}
};