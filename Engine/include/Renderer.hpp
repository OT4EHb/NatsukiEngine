#pragma once
#include <Window.hpp>
#include <vector>
#include <string>
class Renderer {
private:
	SDL_Renderer *renderer;
public:
	Renderer(Window *window, const std::string &name);
	Renderer(Window *window, const char *name = nullptr);
	~Renderer();
	static const std::vector<std::string> &getDrivers();
	virtual bool setDrawColor(const SDL_Color &c) const;
	virtual bool clear(const SDL_Color &color = {0, 0, 0, 255}) const;
	virtual bool present() const;
	virtual bool fillRect(const SDL_FRect *rect) const;
	virtual bool rect(const SDL_FRect *rect) const;
};