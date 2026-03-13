module;
#include <cstddef>
#include <string_view>
#include <SDL3_ttf/SDL_ttf.h>
export module Natsuki.UI.Text;
export import Natsuki.UI.Font;
export import Natsuki.Exception;
export import Natsuki.UI.TextEngine;
export import Natsuki.ECS.Component.Color;

export using ::size_t;
export using ::SDL_Point;

export namespace Natsuki {
	class Text {
	private:
		TTF_Text *text;
	public:
		inline Text(TextEngine& , Font &, std::string_view);
		inline ~Text();
		inline operator TTF_Text *() {
			return text;
		}
		inline bool render();
		inline bool set(std::string_view);
		inline bool setPosition(SDL_Point);
		inline bool setFont(Font &);
		inline bool setColor(const Color&);
		inline bool setWrapWidth(size_t width);
		inline bool insert(size_t offset, std::string_view);
		inline bool append(std::string_view);
		inline SDL_Point getSize();
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

bool Text::setFont(Font &font) {
	return TTF_SetTextFont(text, font);
}

bool Text::setColor(const Color &color) {
	return TTF_SetTextColor(text, color.r, color.g, color.b, color.a);
}

bool Text::setWrapWidth(size_t width) {
	return TTF_SetTextWrapWidth(text, static_cast<int>(width));
}

bool Text::insert(size_t offset, std::string_view str) {
	return TTF_InsertTextString(text, static_cast<int>(offset), str.data(), str.size());
}

bool Text::append(std::string_view str) {
	return TTF_AppendTextString(text, str.data(), str.size());
}

SDL_Point Text::getSize() {
	SDL_Point p;
	checkCallSDL(TTF_GetTextSize(text,&p.x, &p.y));
	return p;
}