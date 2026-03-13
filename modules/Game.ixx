module;
#include <concepts>
#include <stdexcept>
#include <string_view>
#include <SDL3/SDL_init.h>
export module Natsuki.Game;
import Natsuki.MessageBox;

#define checkException(func) try func \
catch (const std::runtime_error &e) { \
	Natsuki::MessageBox() \
	.setTitle("Runtime Error") \
	.setFlag(Natsuki::MessageBox::Flags::ERROR) \
	.setMessage(e.what()) \
	.show(); \
	return SDL_APP_FAILURE; \
}

export namespace Natsuki {
	template<class T>
	class Game {
	private:
		static T *getGame(void *appstate) {
			return static_cast<T *>(appstate);
		}
	public:
		static SDL_AppResult AppInit(void **appstate, int argc, char **argv) {
			checkException(
				{
					auto *game = new T(); *appstate = game;
				}
			);
			return SDL_APP_CONTINUE;
		}

		static SDL_AppResult AppIterate(void *appstate) {
			auto *game = getGame(appstate);
			checkException(
				{
					return (game->iterate());
				}
			);
		}

		static SDL_AppResult AppEvent(void *appstate, SDL_Event *event) {
			auto *game = getGame(appstate);
			checkException(
				{
					return (game->eventHandler(*event));
				}
			);
		}

		static void AppQuit(void *appstate, SDL_AppResult result) {
			auto *game = getGame(appstate);
			if (game) {
				delete game;
			}
		}
	};

	template <class T>
	concept GameConcept = requires(T game, SDL_Event & event) {
		{ game.iterate() }->std::convertible_to<SDL_AppResult>;
		{ game.eventHandler(event) }->std::convertible_to<SDL_AppResult>;
		std::default_initializable<T>;
	};
}