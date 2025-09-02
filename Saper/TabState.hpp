#pragma once
#include <iostream>
#include "pch.h"
#include "Natsuki.hpp"
class TabState :
    public KeyState {
    TabState();
    static TabState instance;
public:
    static TabState *get();
    void update(GameSystems *systems, Uint64 deltaTime) override;
    void render(GameSystems *systems) override;
};
