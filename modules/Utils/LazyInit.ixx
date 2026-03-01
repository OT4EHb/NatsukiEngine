module;
#include <concepts>
#include <optional>
export module Natsuki.Utils.LazyInit;

export namespace Natsuki {
	template<class T>
	class LazyInit {
	private:
		std::optional<T> value;
	public:
		constexpr inline LazyInit() = default;

		constexpr explicit inline operator bool() {
			return value.has_value();
		}

		template<class...Args>
			requires std::constructible_from<T, Args...>
		constexpr inline void init(Args&&...args) {
			value.emplace(std::forward<Args>(args)...);
		}

		constexpr inline void reset() {
			value.reset();
		}

		constexpr inline T *operator->() {
			return value.operator->();
		}

		constexpr inline const T *operator->() const {
			return value.operator->();
		}

		constexpr inline T &operator*() & {
			return *value;
		}

		constexpr inline const T &operator*() const & {
			return *value;
		}

		constexpr inline T &&operator*() && {
			return std::move(*value);
		}

		constexpr inline const T &&operator*() const && {
			return std::move(*value);
		}
	};
}