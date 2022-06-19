#pragma once
#include "Spark.h"

class Projectile : public FireworkObject
{
public:
	explicit Projectile(const Coord& startPosition, const Force& force, const double lifeSpan) :
		FireworkObject(startPosition, force, lifeSpan, colorRandomizer(), ROCKET_DISPLAY_SYMBOL),
		_isDetonated{},
		_isAllFireCrackersDetonated{},
		_fireCrackers{}
	{
		initSparks();
	};
	
	const std::list<std::shared_ptr<FireworkObject>>& fireCrackers() const {
		return _fireCrackers;
	}
	
	bool isDetonated() const {
		return _isDetonated;
	}

	void fly() override {
		double flightTime{ _timer.secsElapsedSinceStart() };

		if (flightTime <= _lifeSpan) {
			Coord newCoord{ calcFlightTrajectory(_location[LAUNCH_LOCATION], _force, flightTime) };
			updateLocation(newCoord);
		}
		else {
			if (!_isDetonated) {
				_isDetonated = true;
				for (auto& obj : _fireCrackers) {
					obj->initTimer();
				}
			}

			for (auto& obj : _fireCrackers) {
				if (!obj->isEpxloded()) {
					obj->fly();
				}
			}
			
			_isAllFireCrackersDetonated = std::all_of(_fireCrackers.begin(), _fireCrackers.end(),
				[](const std::shared_ptr<FireworkObject>& obj) {
					return obj->isEpxloded();
				});
		}
		if (_isAllFireCrackersDetonated && _isDetonated) {
			_isExploded = true;
		}
	}

	virtual ~Projectile() = default;

protected:

	bool _isDetonated;
	bool _isAllFireCrackersDetonated;
	std::list<std::shared_ptr<FireworkObject>> _fireCrackers;

	void initSparks() {
		eColor color{ colorRandomizer() };

		double sparkLifeSpan{ _lifeSpan / 2 };

		double sparkVelocity{ _force._velocity * _lifeSpan / sparkLifeSpan  };

		Coord locationAtExplosion{ calcFlightTrajectory(_location[LAUNCH_LOCATION], _force, _lifeSpan)};

		size_t noOfSparks{ static_cast<size_t>(randNumGenerator(MAX_NO_OF_SPARKS, MIN_NO_OF_SPARKS)) };

		for (size_t i{}; i < noOfSparks; i++) {

			Force sparkForce(directionRandomizer(), sparkVelocity);
			_fireCrackers.emplace_back(new Spark(locationAtExplosion, sparkForce, sparkLifeSpan, color));

		}
	}

	size_t directionRandomizer() const {
		size_t trajectoryAngle{ 360 };
		return rand() % 360;
	}

	eColor colorRandomizer() const {
		return static_cast<eColor>((rand() % NO_OF_COLORS) + 1);
	}
};
