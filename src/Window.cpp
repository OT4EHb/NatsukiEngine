#include <SDL3/SDL_video.h>
#include <Window.hpp>

Window::Window(SDL_Window *window) :window(window) {}

Window::Window(const char *title, int width, int height, SDL_WindowFlags flags) :
	window(SDL_CreateWindow(title, width, height, flags)) {}

Window::~Window() {
	SDL_DestroyWindow(window);
}
