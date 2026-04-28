module;
#include <concepts>
export module Natsuki.State.Concept;

export namespace Natsuki {
	template<class T>
	concept HasEnter = requires(T state) {
		{ state.enter() }->std::same_as<void>;
	}

	template<class T>
	concept HasExit = requires(T state) {
		{ state.exit() }->std::same_as<void>;
	}
}