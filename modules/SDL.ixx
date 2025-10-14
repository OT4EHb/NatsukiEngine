#include <SDL3/SDL_init.h>
export module SDL;

export class SDL {
public:
	SDL() = delete;
	static bool init(SDL_InitFlags flags=SDL_INIT_VIDEO);
	static void quit();
	static const char *getError();
};