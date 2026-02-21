module;
#include <cstddef>
export module Natsuki.Utils.FlagsOperation;

using B = size_t;

export namespace Natsuki {
	template <class T>
	constexpr T operator|(T lft, T rht) {
		return static_cast<T>(static_cast<B>(lft) | static_cast<B>(rht));
	}

	template <class T>
	constexpr T operator&(T lft, T rht) {
		return static_cast<T>(static_cast<B>(lft) & static_cast<B>(rht));
	}

	template <class T>
	constexpr T &operator|=(T &lft, T rht) {
		return reinterpret_cast<T &>(reinterpret_cast<B &>(lft) |= reinterpret_cast<B &>(rht));
	}

	template <class T>
	constexpr T &operator&=(T &lft, T rht) {
		return reinterpret_cast<T &>(reinterpret_cast<B &>(lft) &= reinterpret_cast<B &>(rht));
	}
}