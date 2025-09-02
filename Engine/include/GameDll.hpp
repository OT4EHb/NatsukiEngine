#pragma once
#include <Windows.h>
#include <GameState.hpp>

class GameDll {
	typedef GameState *(*InitGameFunc)();
private:
	HMODULE dll;
	GameDll(const char *name) {
		dll = LoadLibraryA(name);
	}
public:
	static GameState *init(const char *name) {
		static GameDll instance(name);
		if (!instance.isLoaded()) {
			return nullptr;
		}
		auto create = (InitGameFunc)GetProcAddress(instance.dll, "createStartState");
		if (create == nullptr) return nullptr;
		return create();
	}
	bool isLoaded() const {
		return dll != nullptr;
	}
	~GameDll() {
		if (isLoaded())
			FreeLibrary(dll);
	}
};