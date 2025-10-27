module;
class Renderer;
class MessageBox;
export module Window;
import <SDL3/SDL_video.h>;
import SDLException;

export class Window {
	friend class Renderer;
	friend class MessageBox;
private:
	SDL_Window *window;
public:
	inline Window(SDL_Window *window);
	inline Window(const char *title, int width, int height, SDL_WindowFlags flags = 0);
	inline ~Window();
	inline bool show();
	inline bool hide();
	inline Window *createPopupWindow(int offset_x, int offset_y, int width, int height, SDL_WindowFlags flags = SDL_WINDOW_TOOLTIP);
	inline bool flash(SDL_FlashOperation operation = SDL_FLASH_CANCEL);
	inline bool raise();
};

Window::Window(SDL_Window *window) :window(window) {}

Window::Window(const char *title, int width, int height, SDL_WindowFlags flags) :
	window(SDL_CreateWindow(title, width, height, flags)) {
	if (window == nullptr)
		throw SDLException();
}

Window::~Window() {
	SDL_DestroyWindow(window);
}

bool Window::show() {
	return SDL_ShowWindow(window);
}

bool Window::hide() {
	return SDL_HideWindow(window);
}

Window *Window::createPopupWindow(int offset_x, int offset_y, int width, int height, SDL_WindowFlags flags) {
	return new Window(SDL_CreatePopupWindow(window, offset_x, offset_y, width, height, flags));
}

bool Window::flash(SDL_FlashOperation operation) {
	return SDL_FlashWindow(window, operation);
}

bool Window::raise() {
	return SDL_RaiseWindow(window);
}