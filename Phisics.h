#pragma once
#include <cmath>
#include <stdint.h>
#include "Coord.h"

#define G_FORCE 9.81f
#define PI 3.14159265f

#define MAX_LIFE_SPAN 2.0f
#define MIN_LIFE_SPAN 1.0f

#define MAX_VELOCITY 20.0f
#define MIN_VELOCITY 10.0f

#define MAX_TRAJECTORY_ANGLE 120
#define MIN_TRAJECTORY_ANGLE 60

#define WIDTH_HEIGHT_RATIO 2

struct Force;

double degreeToRad(const size_t degree);

double calcVelocityX(const size_t angleInDeg, const double velocity);

double calcVelocityY(const size_t angleInDeg, const double velocity);

Coord calcFlightTrajectory(const Coord& originalPos, const Force& force, const double time);

double randNumGenerator(const double max, const double min);

struct Force {
	Force() = default;
	explicit Force(const size_t angleInDeg, const double velocity) :
		_forceDirectionInDeg{ angleInDeg },
		_velocity{ velocity },
		_velocityX{ calcVelocityX(_forceDirectionInDeg, _velocity) },
		_velocityY{ calcVelocityY(_forceDirectionInDeg, _velocity) }
	{};
	size_t _forceDirectionInDeg;
	double _velocity;
	double _velocityX;
	double _velocityY;
};


