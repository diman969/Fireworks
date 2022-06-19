#pragma once
#include <chrono>

#define NANO_IN_SEC 1000000000.0

class Timer
{
public:
	Timer() = default;

	void initTimer() {
		_startTime = std::chrono::steady_clock::now();
		_timeStemp = _startTime;
	}

	double secsElapsedSinceStart() const {
		return (std::chrono::steady_clock::now() - _startTime).count() / NANO_IN_SEC;
	}
private:
	std::chrono::steady_clock::time_point _startTime;
	std::chrono::steady_clock::time_point _timeStemp;
};

