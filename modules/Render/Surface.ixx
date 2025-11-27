module;
class Texture;
export module Surface;
import <string_view>;
import <SDL3_image/SDL_image.h>;

export class Surface {
	friend class Texture;
private:
	SDL_Surface *surface;
public:
	Surface(std::string_view file);
	~Surface();
};

Surface::Surface(std::string_view file) {
	surface = IMG_Load(file.data());
}

Surface::~Surface() {
	SDL_DestroySurface(surface);
}