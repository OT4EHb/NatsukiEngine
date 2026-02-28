module;
#include <string_view>
#include <SDL3_ttf/SDL_ttf.h>
export module Natsuki.UI.Text;
export import Natsuki.UI.Font;
export import Natsuki.Exception;
import Natsuki.UI.TextEngine;

export using ::SDL_Point;

export namespace Natsuki {
	class Text {
	private:
		TTF_Text *text;
	public:
		inline Text(TextEngine& , Font &, std::string_view);
		inline ~Text();
		inline bool render();
		inline bool set(std::string_view);
		inline bool setPosition(SDL_Point);
	};
}

using namespace Natsuki;

Text::Text(TextEngine& engine, Font &font, std::string_view str) {
	text = TTF_CreateText(engine, font, str.data(), str.size());
	checkCallSDL(text != nullptr);
}

Text::~Text() {
	TTF_DestroyText(text);
}

bool Text::render() {
	return TTF_DrawRendererText(text, 0, 0);
}

bool Text::set(std::string_view str) {
	return TTF_SetTextString(text, str.data(), str.size());
}

bool Text::setPosition(SDL_Point p) {
	return TTF_SetTextPosition(text, p.x, p.y);
}