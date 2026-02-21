module;
#include <string_view>
#include <SDL3_ttf/SDL_ttf.h>
export module Natsuki.UI.Font;
export import Natsuki.Exception;
export import Natsuki.Utils.FlagsOperation;

export namespace Natsuki {
	class Font {
	public:
		enum class Style : TTF_FontStyleFlags {
			NORMAL = TTF_STYLE_NORMAL,
			BOLD = TTF_STYLE_BOLD,
			ITALIC = TTF_STYLE_ITALIC,
			UNDERLINE = TTF_STYLE_UNDERLINE,
			STRIKETHROUGH = TTF_STYLE_STRIKETHROUGH
		};
	private:
		TTF_Font *font{nullptr};
	public:
		inline Font() = default;
		inline ~Font();
		inline operator TTF_Font *() {
			return font;
		}
		inline bool load(std::string_view path, float ptsize);
		inline bool setSize(float ptsize);
		inline bool setSizeDPI(float ptsize, int hdpi, int vdpi);
		inline float getSize();
		inline bool getDPI(int *hdpi, int *vdpi);
		inline void setStyle(Style);
	};
}

using namespace Natsuki;

Font::~Font() {
	TTF_CloseFont(font);
}

bool Font::load(std::string_view path, float ptsize) {
	TTF_CloseFont(font);
	font = TTF_OpenFont(path.data(), ptsize);
	return font != nullptr;
}

bool Font::setSize(float ptsize) {
	return TTF_SetFontSize(font, ptsize);
}

bool Font::setSizeDPI(float ptsize, int hdpi, int vdpi) {
	return TTF_SetFontSizeDPI(font, ptsize, hdpi, vdpi);
}

float Font::getSize() {
	return TTF_GetFontSize(font);
}

bool Font::getDPI(int *hdpi, int *vdpi) {
	return TTF_GetFontDPI(font, hdpi, vdpi);
}

void Font::setStyle(Style style) {
	TTF_SetFontStyle(font, static_cast<TTF_FontStyleFlags>(style));
}