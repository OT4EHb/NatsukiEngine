module;
#include <SDL3_ttf/SDL_ttf.h>
export module Natsuki.UI.Text;

export namespace Natsuki {
	class Text {
	private:
		TTF_Text *text;
	public:
		Text();
		~Text();
	};
}

using namespace Natsuki;

Text::Text() {

}

Text::~Text() {

}