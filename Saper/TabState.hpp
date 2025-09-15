#pragma once
#include <iostream>
#include "pch.h"
#include "Natsuki.hpp"
class TabState :
    public KeyState {
public:
    TabState();
    void update(GameSystems *systems, Uint64 deltaTime) override;
    void render(GameSystems *systems) override;
};
