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
	concept include = (std::same_as<T, Args> || ...);

	template <ComponentType...components>
	class ComponentPool {
	private:
		std::tuple<std::vector<components>...>data;
		std::vector<Entity> entitys;
		std::vector<size_t> ids;
		std::vector<size_t> freeIndices;
	public:
		constexpr ComponentPool(size_t size) {
			entitys.resize(size, Entity(-1, -1));
			ids.reserve(size);
			freeIndices.reserve(size);
			for (size_t i{}; i < size; ++i) {
				freeIndices.push_back(size - 1 - i);
			}
			std::apply(
				[size](auto&...vec) {
					(vec.reserve(size), ...);
				}, data);
		}

		constexpr inline size_t getSize() {
			return std::get<0>(data).size();
		}

		constexpr bool isValid(Entity entity) {
			if (entitys.size() <= entity.id) return false;
			return entitys[entity.id] == entity;
		}

		[[nodiscard]] constexpr Entity addEntity() {
			if (freeIndices.empty()) {
				throw Exception("ComponentPool overflow, specify a larger value during initialization.");
			}
			auto it = freeIndices.end() - 1;
			size_t capacity = *it;
			freeIndices.erase(it);
			entitys[capacity] = Entity(entitys[capacity].gen + 1, capacity);
			ids.push_back(capacity);
			std::apply(
				[](auto&...vec) {
					(vec.emplace_back(), ...);
				}, data
			);
			return entitys[capacity];
		}

		constexpr bool dropEntity(Entity entity) {
			if (!isValid(entity)) return false;
			Entity& finder = entitys[entity.id];
			size_t last = getSize();
			if (finder.id + 1 < last) {
				std::apply(
					[index=finder.id, size = last - 1](auto&...vec) {
						((vec[index] = vec[size]), ...);
					}, data
				);
				entitys[ids[last - 1]] = finder;
				ids[finder.id] = ids[last - 1];
			}
			std::apply(
				[](auto&...vec) {
					(vec.pop_back(), ...);
				}, data
			);
			ids.pop_back();
			entitys[entity.id].id = -1;
			freeIndices.push_back(entity.id);
			return true;
		}

		template <ComponentType T>
			requires include<T, components...>
		constexpr T &getComponent(Entity entity) {
			if (!isValid(entity)) {
				throw Exception("Invalid Natsuki::Entity");
			}
			return getComponent<T>()[entitys[entity.id].id];
		}

		template <ComponentType T>
			requires include<T, components...>
		constexpr T &getComponent(size_t id) {
			return getComponent<T>()[id];
		}

		template <ComponentType T>
			requires include<T, components...>
		constexpr auto &getComponent() {
			return std::get<std::vector<T>>(data);
		}
	};
}