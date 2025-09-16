#pragma once
#include <Windows.h>
#include <GameState.hpp>

class GameDll {
	typedef void (*InitGameFunc)(GameSystems *);
private:
	HMODULE dll;
	GameDll(const char *name) {
		dll = LoadLibraryA(name);
	}
public:
	static void init(const char *name, GameSystems *systems) {
		static GameDll instance(name);
		if (!instance.isLoaded()) {
			return;
		}
		auto create = (InitGameFunc)GetProcAddress(instance.dll, "createStartState");
		if (create == nullptr) return;
		return create(systems);
	}
	bool isLoaded() const {
		return dll != nullptr;
	}
	~GameDll() {
		if (isLoaded())
			FreeLibrary(dll);
	}
};