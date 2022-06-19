#pragma once
#include <list>
#include <algorithm>
#include <memory>
#include "Timer.h"
#include "Phisics.h"

#define NO_OF_COLORS 6

#define NO_OF_SMALL_ROCKETS 2
#define MIN_NO_OF_SPARKS 20
#define MAX_NO_OF_SPARKS 50

#define SPARK_DISPLAY_SYMBOL 'o'
#define ROCKET_DISPLAY_SYMBOL '^'

enum class eColor { BLUE = 1, GREEN, PINK, RED, WHITE, YELLOW };

class FireworkObject
{
public:
	explicit FireworkObject(const Coord& startPosition, const Force& force, const double lifeSpan, const eColor color, const char symbol) :
		_location{ {startPosition}, {startPosition}, {startPosition} },
		_force{force},
		_timer{},
		_lifeSpan{ lifeSpan },
		_color{color},
		_symbol{symbol},
		_isExploded{}
	{};

	Coord curLocation() const {
		return _location[CUR_LOCATION];
	}

	Coord prevLocation() const {
		return _location[PREV_LOCATION];
	}

	const Force& force() const {
		return _force;
	}

	bool isEpxloded() const {
		return _isExploded;
	}

	char dispalySymbol() const {
		return _symbol;
	}

	eColor color() const {
		return _color;
	}

	void initTimer() {
		_timer.initTimer();
	}

	virtual void fly() = 0;

	virtual ~FireworkObject() = default;

protected:
	enum eLocation { LAUNCH_LOCATION, CUR_LOCATION, PREV_LOCATION };

	Coord _location[3];
	Force _force;
	Timer _timer;
	double _lifeSpan;
	eColor _color;
	char _symbol;
	bool _isExploded;
	
	void updateLocation(const Coord& newLoc) {
		_location[PREV_LOCATION] = _location[CUR_LOCATION];
		_location[CUR_LOCATION] = newLoc;
	}
};
