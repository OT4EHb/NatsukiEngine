export module Color;
import <SDL3/SDL_pixels.h>;
export import Component;

export using Color = SDL_Color;

export template<>
struct traitComponent<Color> :std::true_type {};

export bool operator==(const Color &left, const Color &right) {
	return left.r == right.r
		&& left.g == right.g
		&& left.b == right.b
		&& left.a == right.a;
}

export bool operator!=(const Color &left, const Color &right) {
	return !(left == right);
}