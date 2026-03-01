module;
#include <concepts>
export module Natsuki.Utils.FlagsOperation;

export namespace Natsuki {
	template<class T>
	concept Enum = std::is_enum_v<T>;

	template <Enum T>
	constexpr T operator|(T lft, T rht) {
		using B = std::underlying_type_t<T>;
		return static_cast<T>(static_cast<B>(lft) | static_cast<B>(rht));
	}

	template <Enum T>
	constexpr T operator&(T lft, T rht) {
		using B = std::underlying_type_t<T>;
		return static_cast<T>(static_cast<B>(lft) & static_cast<B>(rht));
	}

	template <Enum T>
	constexpr T &operator|=(T &lft, T rht) {
		using B = std::underlying_type_t<T>;
		lft = lft | rht;
		return lft;
	}

	template <Enum T>
	constexpr T &operator&=(T &lft, T rht) {
		using B = std::underlying_type_t<T>;
		lft = lft & rht;
		return lft;
	}

	template <Enum T>
	constexpr T operator~(T val) {
		using B = std::underlying_type_t<T>;
		return static_cast<T>(~static_cast<B>(val));
	}

	template <Enum T>
	constexpr bool has_flag(T val, T flag) {
		return (val & flag) == flag;
	}

	template <Enum T, Enum... Flags>
		requires (std::same_as<T, Flags> && ...)
	constexpr T make_flags(Flags... flags) {
		return (static_cast<T>(0) | ... | flags);
	}
}