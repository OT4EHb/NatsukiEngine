module;
#include <cstddef>
#include <memory>
#include <vector>
export module Natsuki.Render.Animation;
export import Natsuki.Render.Sprite;
export import Natsuki.Time.GlobalTime;

export namespace Natsuki {

	struct AnimationData {
		std::shared_ptr<Texture> texture;
		std::vector<SDL_FRect> frames;
		std::vector<time_type> delays;

		void addFrame(SDL_FRect frame, time_type delay) {
			frames.push_back(frame);
			delays.push_back(delay);
		}

		void addFrame(int x, int y, int w, int h, time_type delay) {
			frames.emplace_back(x, y, w, h);
			delays.push_back(delay);
		}

		void fromGrid(int width, int height, SDL_FPoint size, time_type delay = 100) {
			for (int h = 0.f; h < size.y; h += height)
				for (int w = 0.f; w < size.x; w += width) {
					frames.emplace_back(w, h, width, height);
					delays.push_back(delay);
				}
		}
	};

	struct AnimationState {
		size_t index = 0;
		time_type current = 0;

		void reset() {
			index = 0;
			current = 0;
		}
	};

	class Animation {
	private:
		std::shared_ptr<AnimationData> data;
	public:
		AnimationState state;
		Animation(size_t count):data(std::make_shared<AnimationData>()) {
			data->frames.reserve(count);
			data->delays.reserve(count);
		}

		AnimationData *operator->() { return data.get(); }
		const AnimationData *operator->() const { return data.get(); }

		SDL_FRect &getCurrent() const {
			return data->frames[state.index];
		}

		void update(time_type delta) {
			state.current += delta;
			while (state.current >= data->delays[state.index]) {
				state.current -= data->delays[state.index];
				state.index = (state.index + 1) % data->frames.size();
			}
		}
	};

	template <ComponentType...components>
	struct AnimationPool : public ComponentPool<AnimationState, PositionSize, SpriteOrigin, components...> {
		AnimationData animationData;
	};
}