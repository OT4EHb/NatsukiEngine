module;
#include <cstddef>
export module Natsuki.ECS.Entity;

export using ::size_t;

export namespace Natsuki {
	struct Entity {
		size_t id;
		inline explicit operator size_t&() {
			return id;
		}
		constexpr inline Entity &operator=(size_t other) {
			id = other;
			return *this;
		}
	};
}