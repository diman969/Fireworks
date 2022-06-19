#pragma once
#include "Projectile.h"


class Rocket : public Projectile
{
public:
	using Projectile::Projectile;

	explicit Rocket(const Coord& startingPosition, const size_t angle, const double velocity, const double lifeSpan) :
		Projectile(startingPosition, Force(angle, velocity), lifeSpan)
	{
		initSmallProjectiles();
	};

	void launch() {
		_timer.initTimer();
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
		
			_isExploded = std::all_of(_fireCrackers.begin(), _fireCrackers.end(), 
				[](const std::shared_ptr<FireworkObject>& obj) 
				{
					return obj->isEpxloded();
				}
			);
		}
	}

	~Rocket() = default;

private:

	void initSmallProjectiles() {
		double projectileVelocity{ _force._velocity * 2 };
		double projectileLifeSpan{ _lifeSpan / 2 };

		Coord locationAtExplosion{ calcFlightTrajectory(_location[LAUNCH_LOCATION], _force, _lifeSpan)};

		_fireCrackers.emplace_front(new Projectile(locationAtExplosion, Force(_force._forceDirectionInDeg + 2, projectileVelocity), projectileLifeSpan));
		_fireCrackers.emplace_front(new Projectile(locationAtExplosion, Force(_force._forceDirectionInDeg - 2, projectileVelocity), projectileLifeSpan));
	}
};

