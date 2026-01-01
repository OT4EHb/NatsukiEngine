module;
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
export module Font;
import SDLException;

export class Font {
private:
	TTF_Font *font;
public:
	inline Font(std::string_view path, float);
	inline ~Font();
};

Font::Font(std::string_view path,float p) :
	font(TTF_OpenFont(path.data(),p)) {
	checkCallSDL(font != nullptr);
}

Font::~Font() {
	TTF_CloseFont(font);
}