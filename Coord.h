#pragma once

struct Coord {
	size_t _posX;
	size_t _posY;
	bool operator==(const Coord& other) const {
		return _posX == other._posX && _posY == other._posY;
	}
	bool operator!=(const Coord& other) const {
		return !(*this == other);
	}
};