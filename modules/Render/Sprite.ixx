module;
#include <memory>
export module Natsuki.Render.Sprite;
export import Natsuki.Render.FlipMode;
export import Natsuki.Render.Texture;
export import Natsuki.ECS.ComponentPool;
export import Natsuki.ECS.Component.PositionSize;

export namespace Natsuki {
	struct SpriteSrc :public FRect {
		inline void set(const Texture &texture) {
			x = 0;
			y = 0;
			FPoint &p = reinterpret_cast<FPoint &>
				(*(reinterpret_cast<char *>(this) + sizeof(FPoint)));
			p = texture.getSize();
		}
	};

	struct SpriteOrigin {
		double angle{};
		FPoint center{};

		inline void setCenter(FRect &dstRect) {
			center.x = dstRect.w / 2;
			center.y = dstRect.h / 2;
		}
	};

	struct Sprite {
		std::shared_ptr<Texture> texture;
		SpriteSrc src;
		PositionSize dst;
		SpriteOrigin origin;
		FlipMode flip;
	};

	template <ComponentType...components>
	struct SpritePool : public ComponentPool<SpriteSrc, PositionSize, SpriteOrigin, components...> {
		std::shared_ptr<Texture> texture;
	};
}