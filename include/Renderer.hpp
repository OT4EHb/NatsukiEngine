#pragma once
#include <Natsuki.hpp>

class Window;
struct SDL_Renderer;

class NATSUKI Renderer {
private:
	SDL_Renderer *renderer;
public:
	Renderer(Window *window, const char *name = "");
	~Renderer();
	inline bool setDrawColor(const SDL_Color &c) const;
	inline bool clear(const SDL_Color &color = {0, 0, 0, 255}) const;
	inline bool present() const;
	inline bool fillRect(const SDL_FRect *rect) const;
	inline bool rect(const SDL_FRect *rect) const;
};

