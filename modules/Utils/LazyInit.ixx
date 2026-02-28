module;
#include <concepts>
export module Natsuki.Utils.LazyInit;

export namespace Natsuki {
	template<class T>
	class LazyInit {
	private:
		alignas(T) std::byte buffer[sizeof(T) + 1];
	public:
		constexpr inline LazyInit() {
			buffer[0] = std::byte{false};
		}

		constexpr inline operator bool() {
			return static_cast<bool>(buffer[0]);
		}

		template<class...Args>
		requires std::constructible_from<T, Args...>
		void init(Args&&...args) {
			T* a = new(buffer + 1)T(std::forward<Args>(args)...);
			buffer[0] = std::byte{true};
		}

		inline T* get() {
			return reinterpret_cast<T *>(buffer + 1);
		}
		inline ~LazyInit() {
			if (*this)
				get()->~T();
		}
	};
}