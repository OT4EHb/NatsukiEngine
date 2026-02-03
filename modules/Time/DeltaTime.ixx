export module Natsuki.Time.DeltaTime;
export import Natsuki.Time.GlobalTime;

export namespace Natsuki {
	class DeltaTime {
	private:
		time_type time;
	public:
		inline DeltaTime() :time(GlobalTime::getTicks()) {}
		inline time_type get() const {
			return GlobalTime::getTicks() - time;
		}
		inline time_type update() {
			time_type tmp = get();
			time = GlobalTime::getTicks();
			return tmp;
		}
	};

	class DeltaTimeNS {
	private:
		time_type time;
	public:
		inline DeltaTimeNS() :time(GlobalTime::getTicksNS()) {}
		inline time_type get() const {
			return GlobalTime::getTicksNS() - time;
		}
		inline time_type update() {
			time_type tmp = get();
			time = GlobalTime::getTicksNS();
			return tmp;
		}
	};
}