module;
#include <concepts>
#include <cstddef>
#include <tuple>
#include <vector>
#include <unordered_set>
export module Natsuki.ECS.ECSLogic;
export import Natsuki.ECS.Component;
export import Natsuki.ECS.BaseSystem;

export using ::size_t;

export namespace Natsuki {
	using Entity = size_t;

	template<class T, class...Args>
	concept include = (std::same_as<T, Args> || ...);

	template <ComponentType...components>
	class ECS {
	private:
		std::unordered_set<size_t> noactived;
		std::tuple<std::vector<components>...>data{};
	public:
		ECS(size_t size = 100) {
			noactived.reserve(size);
			std::apply(
				[size](auto&...vec) {
					(vec.reserve(size), ...);
				}, data);
		}

		constexpr inline size_t getSize() {
			return std::get<0>(data).size();
		}

		[[nodiscard]] Entity addEntity() {
			size_t size;
			if (noactived.empty()) {
				size = getSize();
				std::apply(
					[](auto&...vec) {
						(vec.emplace_back(), ...);
					}, data);
			}
			else {
				auto it = noactived.begin();
				size = *it;
				noactived.erase(it);
			}
			return size;
		}

		void dropEntity(size_t index) {
			if (index < getSize())
				noactived.insert(index);
		}

		template <ComponentType T>
			requires include<T, components...>
		T &getComponent(Entity entity) {
			return getComponent<T>()[entity];
		}

		template <ComponentType T>
			requires include<T, components...>
		auto &getComponent() {
			return std::get<std::vector<T>>(data);
		}
	};
}