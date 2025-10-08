#pragma once

struct SDL_Surface;

class Surface {
private:
	SDL_Surface *surface;
public:
	Surface(const char *file);
	~Surface();
};
