#pragma once
#include <SDL3/SDL_video.h>
#include <Natsuki.hpp>

class Renderer;

class NATSUKI Window {
	friend class Renderer;
private:
	SDL_Window *window;
public:
	Window(SDL_Window *window);
	Window(const char *title, int width, int height, SDL_WindowFlags flags = 0);
	~Window();
};
