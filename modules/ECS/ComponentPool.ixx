module;
#include <concepts>
#include <tuple>
#include <vector>
export module Natsuki.ECS.ComponentPool;
export import Natsuki.ECS.Component;
export import Natsuki.ECS.Entity;
import Natsuki.Exception;

export namespace Natsuki {

	template<class T, class...Args>
	concept is_one_of = (std::same_as<T, Args> || ...);

	template <ComponentType...components>
	class ComponentPool {
	private:
		std::tuple<std::vector<components>...>data;
		std::vector<Entity> entities;//entity.id->Entity
		std::vector<size_t> sparse;//entity.id->index in data
		std::vector<size_t> dense;//index in data->entity.id
		std::vector<size_t> freeIds;
	public:
		constexpr ComponentPool(size_t size) {
			entities.resize(size, Entity(-1, -1));
			sparse.resize(size, size_t(-1));
			dense.reserve(size);
			freeIds.reserve(size);
			for (size_t i{}; i < size; ++i) {
				freeIds.push_back(size - 1 - i);
			}
			std::apply(
				[size](auto&...vec) {
					(vec.reserve(size), ...);
				}, data);
		}

		constexpr inline size_t getSize() const {
			return dense.size();
		}

		constexpr bool isValid(Entity entity) const {
			return entity.id < sparse.size() &&
				entities[entity.id] == entity &&
				sparse[entity.id] < dense.size() &&
				dense[sparse[entity.id]] == entity.id;
		}

		[[nodiscard]] constexpr Entity addEntity() {
			if (freeIds.empty()) {
				throw Exception("ComponentPool overflow, specify a larger value during initialization.");
			}

			auto id = freeIds.back();
			freeIds.pop_back();

			Entity newEntity(entities[id].gen + 1, id);
			entities[id] = newEntity;

			auto index = dense.size();
			dense.push_back(id);
			sparse[id] = index;

			std::apply(
				[](auto&...vec) {
					(vec.emplace_back(), ...);
				}, data
			);
			return newEntity;
		}

		constexpr bool dropEntity(Entity entity) {
			if (!isValid(entity) || dense.empty()) return false;
			auto index = sparse[entity.id];
			size_t last = dense.size() - 1;
			if (index != last) {
				auto movingId = dense[last];
				std::apply(
					[index, last](auto&...vec) {
						((vec[index] = std::move(vec[last])), ...);
					}, data
				);
				sparse[movingId] = index;
				dense[index] = movingId;
			}
			std::apply(
				[](auto&...vec) {
					(vec.pop_back(), ...);
				}, data
			);
			dense.pop_back();
			freeIds.push_back(entity.id);
			entities[entity.id].id = -1;
			sparse[entity.id] = -1;
			return true;
		}

		template <ComponentType T>
			requires is_one_of<T, components...>
		constexpr T &getComponent(Entity entity) {
			if (!isValid(entity)) [[unlikely]] {
				throw Exception("Invalid Natsuki::Entity");
			}
			return getComponent<T>()[sparse[entity.id]];
		}

		template <ComponentType T>
			requires is_one_of<T, components...>
		constexpr T &getComponent(size_t id) {
			if (id>=getSize()) [[unlikely]] {
				throw Exception("Component index out of range");
			}
			return getComponent<T>()[id];
		}

		template <ComponentType T>
			requires is_one_of<T, components...>
		constexpr auto &getComponent() {
			return std::get<std::vector<T>>(data);
		}
	};
}