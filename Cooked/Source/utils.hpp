#pragma once

#include "AEEngine.h"

class Timer {
private:
	f64 countdownDuration; //countdown in s
	f64 startTime; //start time in s

public:
	Timer(f64 duration);

	void start();

	f64 getRemainingTime() const;

	bool completed() const;
};