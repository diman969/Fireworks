#pragma once
#include "Rocket.h"

class Cannon
{
public:
	static Cannon& getInstance() {
		if (!_instance.get()) {
			Cannon::_instance.reset(new Cannon());
		}
		return *Cannon::_instance;
	}
	
	void setPosition(const Coord& newPosition) {
		_position = newPosition;
	}

	Coord position() const {
		return _position;
	}
	
	~Cannon() = default;
	
	std::shared_ptr<Rocket> load() const  {
		Coord position{_position};
		position._posY -= 1;
		std::shared_ptr<Rocket> temp{
			new Rocket(position, randNumGenerator(MAX_TRAJECTORY_ANGLE, MIN_TRAJECTORY_ANGLE), randNumGenerator(MAX_VELOCITY, MIN_VELOCITY), randNumGenerator(MAX_LIFE_SPAN, MIN_LIFE_SPAN)) 
		};
		return temp;
	}

	Cannon(const Cannon& other) = delete;
	Cannon(Cannon&& other) = delete;
	Cannon& operator=(const Cannon& other) = delete;
private:
	Cannon() :
		_position{}
	{};
	Coord _position;
	static std::shared_ptr<Cannon> _instance;
};


