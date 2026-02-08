module;
#include <concepts>
#include <cstddef>
#include <tuple>
#include <vector>
#include <unordered_map>
export module Natsuki.ECS.ECSLogic;
export import Natsuki.ECS.Component;
export import Natsuki.ECS.BaseSystem;

export using ::size_t;

class ECSIterator {
private:
	std::unordered_map<size_t, size_t>::iterator it;
public:
	ECSIterator(std::unordered_map<size_t, size_t>::iterator it)
		: it(it) {

	}

	size_t operator*() const {
		return it->first;
	}

	ECSIterator &operator++() {
		++it;
		return *this;
	}

	ECSIterator operator++(int) {
		ECSIterator temp = *this;
		++(*this);
		return temp;
	}

	bool operator==(const ECSIterator &other) const {
		return it == other.it;
	}
};

export namespace Natsuki {
	using Entity = size_t;

	template<class T, class...Args>
	concept include = (std::same_as<T, Args> || ...);

	template <ComponentType...components>
	class ECS {
	private:
		std::tuple<std::vector<components>...>data;
		std::unordered_map<Entity, size_t> sparse;
		std::vector<Entity> ids;
		size_t capacity{};
	public:
		constexpr ECS(size_t size = 100) {
			sparse.reserve(size);
			ids.reserve(size);
			std::apply(
				[size](auto&...vec) {
					(vec.reserve(size), ...);
				}, data);
		}

		constexpr inline size_t getSize() {
			return std::get<0>(data).size();
		}

		[[nodiscard]] constexpr Entity addEntity() {
			sparse[capacity] = getSize();
			ids.push_back(capacity);
			std::apply(
				[](auto&...vec) {
					(vec.emplace_back(), ...);
				}, data
			);
			return capacity++;
		}

		constexpr bool dropEntity(Entity entity) {
			auto it = sparse.find(entity);
			if (it != sparse.end()) {
				size_t index = it->second;
				size_t last = getSize();
				if (index + 1 < last) {
					std::apply(
						[index, size = last - 1](auto&...vec) {
							((vec[index] = vec[size]), ...);
						}, data
					);
					sparse[ids[last - 1]] = index;
					ids[index] = ids[last - 1];
				}
				std::apply(
					[](auto&...vec) {
						(vec.pop_back(), ...);
					}, data
				);
				ids.pop_back();
				sparse.erase(it);
				return true;
			}
			return false;
		}

		constexpr inline ECSIterator begin() {
			return ECSIterator(sparse.begin());
		}

		constexpr inline ECSIterator end() {
			return ECSIterator(sparse.end());
		}

		template <ComponentType T>
			requires include<T, components...>
		constexpr T &getComponent(Entity entity) {
			return getComponent<T>()[sparse.at(entity)];
		}

		template <ComponentType T>
			requires include<T, components...>
		constexpr auto &getComponent() {
			return std::get<std::vector<T>>(data);
		}
	};
}