module;
#include <string_view>
#include <SDL3/SDL_video.h>
export module Natsuki.Window;
import Natsuki.Exception;
export import Natsuki.Utils.View;

export using ::SDL_WindowID;

export namespace Natsuki {
	class Window {
	public:
		using NatsukiView = void;
	private:
		SDL_Window *window;

		Window(SDL_Window *window) :window(window) {};
	public:
		operator SDL_Window *() {
			return window;
		}
		Window(std::string_view title, int width, int height, SDL_WindowFlags flags = 0) :
			window(SDL_CreateWindow(title.data(), width, height, flags)) {
			checkCall(window != nullptr);
		}
		~Window() {
			SDL_DestroyWindow(window);
		}
		static View<Window> getFromID(SDL_WindowID id) {
			View<Window> view;
			view->window = SDL_GetWindowFromID(id);
			return view;
		}

		bool show() {
			return SDL_ShowWindow(window);
		}
		bool hide() {
			return SDL_HideWindow(window);
		}

		Window *createPopupWindow(int offset_x, int offset_y,
										 int width, int height,
										 SDL_WindowFlags flags = SDL_WINDOW_TOOLTIP) {
			return new Window(SDL_CreatePopupWindow(window, offset_x, offset_y, width, height, flags));
		}

		bool flash(SDL_FlashOperation operation = SDL_FLASH_CANCEL) {
			return SDL_FlashWindow(window, operation);
		}
		bool raise() {
			return SDL_RaiseWindow(window);
		}

		SDL_Point getSize() {
			SDL_Point p;
			SDL_GetWindowSize(window, &p.x, &p.y);
			return p;
		}
		bool setSize(SDL_Point p) {
			return SDL_SetWindowSize(window, p.x, p.y);
		}
		bool setSize(int w, int h) {
			return SDL_SetWindowSize(window, w, h);
		}
	};
}