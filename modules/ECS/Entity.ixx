module;
#include <cstdint>
export module Natsuki.ECS.Entity;

export using ::uint32_t;

export namespace Natsuki {
	struct Entity {
		uint32_t gen;
		uint32_t id;

		bool operator==(const Entity &ent)const {
			return gen == ent.gen && id == ent.id;
		}
	};
}