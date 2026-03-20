module;
#include <cstddef>
#include <memory>
#include <vector>
export module Natsuki.Render.Animation;
export import Natsuki.Render.Sprite;
export import Natsuki.Time.GlobalTime;

export namespace Natsuki {
	class Animation {
	private:
		std::shared_ptr<Texture> texture;
		std::vector<SDL_FRect> frames;
		size_t index = 0;
		time_type delays;//ms
		time_type current = 0;
	public:
		Animation(size_t count, time_type delays) :delays(delays) {
			frames.reserve(count);
		}
		operator Texture &() {
			return *texture.get();
		}
		SDL_FRect &getCurrent() {
			return frames[index];
		}
		void setTexture(std::shared_ptr<Texture> ptr) {
			texture = ptr;
		}
		void bind(int width, int height) {
			frames.resize(0);
			auto size = texture->getSize();
			for (int h=0.f;h<size.y;h+=height)
				for (int w = 0.f; w < size.x; w += width) {
					frames.emplace_back(w, h, width, height);
			}
		}
		void update(time_type delta) {
			current += delta;
			if (current >= delays) {
				index = (index + 1) % frames.size();
				current -= delays;
			}
		}
	};

	template <ComponentType...components>
	struct AnimationPool : public ComponentPool<Animation, PositionSize, SpriteOrigin, components...> {

	};
}