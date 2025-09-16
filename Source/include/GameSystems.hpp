#pragma once
#include <SourceManager.hpp>
#include <StateManager.hpp>
#include <Renderer.hpp>
#include <KeyState.hpp>
#include <GlobalTime.hpp>
class GameSystems {
private:
    GameSystems() = default;
public:
    SourceManager<Window> windowManager;
    SourceManager<Renderer> rendererManager;
    StateManager stateManager;
    ~GameSystems() = default;
    static GameSystems *get() {
        static GameSystems systems;
        return &systems;
    }
};