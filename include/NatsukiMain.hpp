#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <concepts>
import Natsuki.Game;

#define SET_GAME(GameClass) \
    static_assert(std::derived_from<GameClass, Natsuki::Game<GameClass> >, \
                  #GameClass " must inherit from Natsuki::Game<" #GameClass ">"); \
    static_assert(Natsuki::GameConcept<GameClass>, \
                  #GameClass " must comply with the concept Natsuki::GameConcept (defined in Game.ixx)"); \
    extern "C" { \
        SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) { \
            return GameClass::AppInit(appstate, argc, argv); \
        } \
        SDL_AppResult SDL_AppIterate(void *appstate) { \
            return GameClass::AppIterate(appstate); \
        } \
        SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) { \
            return GameClass::AppEvent(appstate, event); \
        } \
        void SDL_AppQuit(void *appstate, SDL_AppResult result) { \
            GameClass::AppQuit(appstate, result); \
        } \
    }