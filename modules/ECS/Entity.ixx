module;
#include <cstdint>
export module Natsuki.ECS.Entity;

export using ::uint64_t;

export namespace Natsuki {
	struct Entity {
		uint64_t gen : 40;
		uint64_t id : 24;

		bool operator==(const Entity &ent)const {
			return gen == ent.gen && id == ent.id;
		}
	};
}