#pragma once
#include <SDL3/SDL_render.h>

class Renderer;

class Window {
	friend class Renderer;
private:
	SDL_Window *window;
public:
	Window(const char *title,int width,int height,SDL_WindowFlags flags=0) :
		window(SDL_CreateWindow(title, width, height, flags)){	}
	~Window() { SDL_DestroyWindow(window); }
};
