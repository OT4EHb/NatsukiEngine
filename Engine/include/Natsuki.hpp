#pragma once
#include <GameSystems.hpp>
#ifdef NATSUKI_IMPORT
#define NATSUKI_API __declspec(dllimport)
#else
#define NATSUKI_API __declspec(dllexport)
#endif

extern "C" NATSUKI_API GameState *createStartState();