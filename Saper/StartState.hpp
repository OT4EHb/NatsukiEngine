#pragma once
#include <iostream>
#include "pch.h"
#include <Natsuki.hpp>
#include <SDL3/SDL_timer.h>
class StartState :
    public KeyState {
public:
    StartState();
    void update(GameSystems *systems, Uint64 deltaTime) override;
    void render(GameSystems *systems) override;
};