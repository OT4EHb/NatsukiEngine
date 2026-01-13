export module Natsuki.FPSCounter;
import Natsuki.Render;
import Natsuki.Time;

export namespace Natsuki {
	class FPSCounter {
	private:
		DeltaTime deltaTime{};
		double smoothedFPS{60};
		Uint64 factFPS{60};
		Uint64 frameCounter{0};
		Uint64 secondAccumulator{0};
		double EMAcoof;
	public:
		FPSCounter(double=0.9);
		double update();
		inline double getFactFPS() const;
		inline double getFrameTime() const;
	};
}

using namespace Natsuki;

FPSCounter::FPSCounter(double coof) :EMAcoof(coof) {
	if (coof > 1.) EMAcoof = 1.;
	else if (coof < 0.1) EMAcoof = 0.1;
}

double FPSCounter::update() {
	Uint64 delta = deltaTime.update();
	if (delta == 0) delta = 1;
	double fps = 1000. / delta;
	smoothedFPS = EMAcoof * fps + (1. - EMAcoof) * smoothedFPS;
	++frameCounter;
	secondAccumulator += delta;
	if (secondAccumulator >= 1000) {
		factFPS = frameCounter;
		secondAccumulator = 0;
		frameCounter = 0;
	}
	return smoothedFPS;
}

double FPSCounter::getFactFPS() const {
	return factFPS;
}

double FPSCounter::getFrameTime() const {
	return 1000./smoothedFPS;
}