module;
#include <string_view>
#include <SDL3_ttf/SDL_ttf.h>
export module Natsuki.UI.Font;
import Natsuki.Exception;

export namespace Natsuki {
	class Font {
	private:
		TTF_Font *font{nullptr};
	public:
		inline Font() = default;
		inline ~Font();
		inline operator TTF_Font *() {
			return font;
		}
		inline bool load(std::string_view path, float size);
	};
}

using namespace Natsuki;

Font::~Font() {
	TTF_CloseFont(font);
}

bool Font::load(std::string_view path, float size) {
	font = TTF_OpenFont(path.data(), size);
	return font != nullptr;
}