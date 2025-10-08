#pragma once
struct SDL_Texture;
class Renderer;

class Texture {
private:
	SDL_Texture *texture;
public:
	Texture(Renderer *renderer, const char *file);
	~Texture();
};