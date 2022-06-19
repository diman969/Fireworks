#include "Phisics.h"

double degreeToRad(const size_t degree) {
	return (degree / 180.0) * (PI);
}

double calcVelocityX(const size_t angleInDeg, const double velocity)
{
	double angleInRad{ degreeToRad(angleInDeg) };
	return velocity * cos(angleInRad);
}

double calcVelocityY(const size_t angleInDeg, const double velocity) {
	double angleInRad{ degreeToRad(angleInDeg) };
	return velocity * sin(angleInRad);
}

Coord calcFlightTrajectory(const Coord& originalPos, const Force& force, const double time) {

	double angleInRad{ degreeToRad(force._forceDirectionInDeg) };
	
	double posX{ force._velocityX * time };
	double posY{ originalPos._posY - (posX * tan(angleInRad) - G_FORCE * pow(posX, 2) / (2 * pow(force._velocity, 2) * (pow(cos(angleInRad), 2)))) };
	
	return { static_cast<size_t>(posX * WIDTH_HEIGHT_RATIO + originalPos._posX), static_cast<size_t>(posY) };
	
}

double randNumGenerator(const double max, const double min) {

	return min + static_cast<float>(rand()) / (RAND_MAX / (max - min));

}
