export module Surface;
import <SDL3_image/SDL_image.h>;

export class Surface {
private:
	SDL_Surface *surface;
public:
	Surface(const char *file);
	~Surface();
};

Surface::Surface(const char *file) {
	surface = IMG_Load(file);
}

Surface::~Surface() {
	SDL_DestroySurface(surface);
}