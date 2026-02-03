export module Natsuki.FPSCounter;
import Natsuki.Render;
import Natsuki.Time;

export namespace Natsuki {
	class FPSCounter {
	private:
		DeltaTimeNS deltaTime{};
		double smoothedFPS{60};
		time_type factFPS{60};
		time_type frameCounter{0};
		time_type secondAccumulator{0};
		double EMAcoof;
	public:
		FPSCounter(double=0.9);
		double update();
		inline time_type getFactFPS() const;
		inline double getFrameTime() const;
	};
}

using namespace Natsuki;

FPSCounter::FPSCounter(double coof) :EMAcoof(coof) {
	if (coof > 1.) EMAcoof = 1.;
	else if (coof < 0.1) EMAcoof = 0.1;
}

double FPSCounter::update() {
	double delta = deltaTime.update();
	if (delta == 0) delta = 1;
	double fps = NS_PER_SECOND / delta;
	smoothedFPS = EMAcoof * fps + (1. - EMAcoof) * smoothedFPS;
	++frameCounter;
	secondAccumulator += delta;
	if (secondAccumulator >= NS_PER_SECOND) {
		factFPS = frameCounter;
		secondAccumulator = 0;
		frameCounter = 0;
	}
	return smoothedFPS;
}

time_type FPSCounter::getFactFPS() const {
	return factFPS;
}

double FPSCounter::getFrameTime() const {
	return 1000./smoothedFPS;
}