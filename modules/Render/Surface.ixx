module;
#include <string_view>
#include <SDL3_image/SDL_image.h>
export module Natsuki.Render.Surface;

export namespace Natsuki {
	class Surface {
	private:
		SDL_Surface *surface;
	public:
		Surface(std::string_view file);
		~Surface();
	};
}

using namespace Natsuki;

Surface::Surface(std::string_view file) {
	surface = IMG_Load(file.data());
}

Surface::~Surface() {
	SDL_DestroySurface(surface);
}