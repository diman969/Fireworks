#pragma once
#include "FireworkObject.h"

class Spark : public FireworkObject
{
public:
	explicit Spark(const Coord curLoc, const Force& force, const double lifeSpan, eColor color) :
		FireworkObject(curLoc, force, lifeSpan, color, SPARK_DISPLAY_SYMBOL)
	{};
	void fly() override {

		double flightTime{ _timer.secsElapsedSinceStart() };

		if (flightTime <= _lifeSpan) {
			Coord newCoord{ calcFlightTrajectory(_location[LAUNCH_LOCATION], _force, flightTime) };
			updateLocation(newCoord);
		}
		else {
			_isExploded = true;
		}
	}

private:

	size_t directionRandomizer() const {
		size_t trajectoryAngle{ 360 };
		return rand() % 360;
	}
};