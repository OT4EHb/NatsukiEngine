export module DeltaTime;
import GlobalTime;

export class DeltaTime {
private:
	Uint64 time;
public:
	inline DeltaTime() :time(GlobalTime::getTicks()) {}
	inline Uint64 get() const {
		return GlobalTime::getTicks() - time;
	}
	inline Uint64 update() {
		Uint64 tmp = get();
		time = GlobalTime::getTicks();
		return tmp;
	}
};

export class DeltaTimeNS {
private:
	Uint64 time;
public:
	inline DeltaTimeNS() :time(GlobalTime::getTicksNS()) {}
	inline Uint64 get() const {
		return GlobalTime::getTicksNS() - time;
	}
	inline Uint64 update() {
		Uint64 tmp = get();
		time = GlobalTime::getTicksNS();
		return tmp;
	}
};