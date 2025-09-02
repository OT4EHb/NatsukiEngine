#include <GameSystems.hpp>

GameSystems::GameSystems() :
    rect(0, 0, 100.f, 100.f),
    currentState(nullptr),
    window("window", 500, 500),
    renderer(&window) {}

GameSystems *GameSystems::get() {
    static GameSystems systems;
    return &systems;
}

bool GameSystems::isValidState() const {
    return currentState != nullptr;
}