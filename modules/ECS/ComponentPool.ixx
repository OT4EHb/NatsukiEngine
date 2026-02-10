module;
#include <concepts>
#include <cstddef>
#include <tuple>
#include <vector>
export module Natsuki.ECS.ComponentPool;
export import Natsuki.ECS.Component;
export import Natsuki.ECS.BaseSystem;
export import Natsuki.ECS.Entity;
import Natsuki.Exception;

export using ::size_t;

class PoolIterator {
private:
	std::vector<size_t>::iterator idIt;
public:
	PoolIterator(std::vector<size_t>::iterator it)
		: idIt(it) {

	}

	Natsuki::Entity operator*() const {
		return Natsuki::Entity(*idIt);
	}

	PoolIterator &operator++() {
		++idIt;
		return *this;
	}

	PoolIterator operator++(int) {
		PoolIterator temp = *this;
		++(*this);
		return temp;
	}

	bool operator==(const PoolIterator &other) const {
		return idIt == other.idIt;
	}
};

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
		constexpr ComponentPool(size_t size = 100) {
			entitys.resize(size, Entity(-1));
			ids.reserve(size);
			freeIndices.reserve(size);
			for (size_t i{}; i < size; ++i) {
				freeIndices.push_back(i);
			}
			std::apply(
				[size](auto&...vec) {
					(vec.reserve(size), ...);
				}, data);
		}

		constexpr inline size_t getSize() {
			return std::get<0>(data).size();
		}

		[[nodiscard]] constexpr Entity addEntity() {
			if (freeIndices.empty()) {
				throw Exception("ComponentPool overflow, specify a larger value during initialization.");
			}
			size_t capacity = freeIndices[0];
			std::swap(*freeIndices.begin(), *(freeIndices.end() - 1));
			freeIndices.resize(freeIndices.size() - 1);
			entitys[capacity] = getSize();
			ids.push_back(capacity);
			std::apply(
				[](auto&...vec) {
					(vec.emplace_back(), ...);
				}, data
			);
			return Entity(capacity);
		}

		constexpr bool dropEntity(Entity entity) {
			if (entitys.size() <= entity.id) return false;
			size_t index = entitys[entity.id].id;
			if (index == -1) return false;
			size_t last = getSize();
			if (index + 1 < last) {
				std::apply(
					[index, size = last - 1](auto&...vec) {
						((vec[index] = vec[size]), ...);
					}, data
				);
				entitys[ids[last - 1]] = index;
				ids[index] = ids[last - 1];
			}
			std::apply(
				[](auto&...vec) {
					(vec.pop_back(), ...);
				}, data
			);
			ids.pop_back();
			entitys[entity.id] = -1;
			freeIndices.push_back(entity.id);
			return true;
		}

		constexpr inline PoolIterator begin() {
			return PoolIterator(ids.begin());
		}

		constexpr inline PoolIterator end() {
			return PoolIterator(ids.end());
		}

		template <ComponentType T>
			requires include<T, components...>
		constexpr T &getComponent(Entity entity) {
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