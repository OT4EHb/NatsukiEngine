export module Natsuki.Render.Camera;
export import Natsuki.ECS.Component.PositionSize;

export namespace Natsuki {
	class Camera :public Position {
	public:
		Camera() :Position{0, 0} {
		}

		FPoint translate(FPoint point) {
			point.x -= x;
			point.y -= y;
			return point;
		}

		FRect translate(FRect rect) {
			rect.x -= x;
			rect.y -= y;
			return rect;
		}
	};
}