module;
#include <concepts>
#include <cstddef>
#include <memory>
export module Natsuki.View;

export namespace Natsuki {
	template<class T>
	class View {
	private:
		alignas(T) std::byte storage[sizeof(T)];
	public:
		template <typename...Args>
		explicit View(Args&&...args) {
			std::construct_at(reinterpret_cast<T *>(storage), std::forward<Args>(args)...);
		}

        T *operator->() noexcept {
            return std::launder(reinterpret_cast<T *>(storage));
        }

        const T *operator->() const noexcept {
            return std::launder(reinterpret_cast<const T *>(storage));
        }

        T &operator*() noexcept {
            return *std::launder(reinterpret_cast<T *>(storage));
        }

        const T &operator*() const noexcept {
            return *std::launder(reinterpret_cast<const T *>(storage));
        }
	};
}