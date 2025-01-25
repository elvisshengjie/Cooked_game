
#include "AEEngine.h"
#include <crtdbg.h>
#include "utils.hpp"





Timer::Timer(f64 duration) : countdownDuration(duration), startTime(0.0) {}

void Timer::start() {
	startTime = AEGetTime(nullptr);
}

f64 Timer::getRemainingTime() const {
	f64 currTime = AEGetTime(nullptr);
	f64 elapsedTime = currTime - startTime;
	return countdownDuration - elapsedTime;
}

bool Timer::completed() const {
	return getRemainingTime() <=0;
}
