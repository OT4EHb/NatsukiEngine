#pragma once
#include <Game.hpp>
#include <Window.hpp>
#include <StateManager.hpp>
class Saper :
    public Game {
private:
    Window window;
public:
    Saper();
    ~Saper();
    SDL_AppResult iterate() override;
    SDL_AppResult eventHandler(SDL_Event*) override;
};

