#include "pch.h"
#include "StartState.hpp"
#include "TabState.hpp"

extern "C" void createStartState(GameSystems *systems) {
	auto window = systems->windowManager.create("main", "main", 500, 500);
	systems->rendererManager.create("main", window);
	systems->stateManager.addState<StartState>();
	systems->stateManager.addState<TabState>();
	systems->stateManager.change<StartState>(systems);
}