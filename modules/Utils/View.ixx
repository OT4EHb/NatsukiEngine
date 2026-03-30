module;
#include <concepts>
#include <cstddef>
#include <memory>
export module Natsuki.Utils.View;

export namespace Natsuki {
    template<typename T>
    concept ViewSafe = requires {
        typename T::NatsukiView;
    };

	template<class T>
	class View {
        static_assert(ViewSafe<T>, "T must have NatsukiView type alias to be used with View");
	private:
		alignas(T) std::byte storage[sizeof(T)];
	public:
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