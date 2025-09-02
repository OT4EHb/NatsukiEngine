#pragma once
#include <Renderer.hpp>
#include <KeyState.hpp>
#include <GlobalTime.hpp>
class GameSystems {
private:
    GameSystems();
public:
    Window window;
    Renderer renderer;
    GameState *currentState;
    SDL_FRect rect;
    ~GameSystems() = default;
    static GameSystems *get();
    void changeState(GameState *state) {
        currentState->exit(this);
        currentState = state;
        currentState->enter(this);
    }
    bool isValidState() const;
};