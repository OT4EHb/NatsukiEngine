module;
#include <SDL3_ttf/SDL_ttf.h>
export module Natsuki.UI.TextEngine;
import Natsuki.Render.Renderer;
import Natsuki.Exception;

export namespace Natsuki {
	class TextEngine {
	private:
		TTF_TextEngine *engine;
	public:
		inline TextEngine(Renderer &);
		inline ~TextEngine();
		inline operator TTF_TextEngine *() {
			return engine;
		}
	};
}

using namespace Natsuki;

TextEngine::TextEngine(Renderer &ren) {
	engine = TTF_CreateRendererTextEngine(ren);
	checkCallSDL(engine != nullptr);
}

TextEngine::~TextEngine() {
	TTF_DestroyRendererTextEngine(engine);
}