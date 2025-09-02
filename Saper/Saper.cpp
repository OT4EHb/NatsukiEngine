#include "pch.h"
#include "StartState.hpp"


extern "C" GameState *createStartState() {
	return StartState::get();
}