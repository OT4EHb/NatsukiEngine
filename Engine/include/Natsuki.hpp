#pragma once
#pragma comment(lib,"SDL3.lib")
#include <GameSystems.hpp>
#ifdef NATSUKI_IMPORT
#define NATSUKI_API __declspec(dllimport)
#else
#define NATSUKI_API __declspec(dllexport)
#endif

extern "C" NATSUKI_API void createStartState(GameSystems* systems);