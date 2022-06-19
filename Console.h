#pragma once
#include <Windows.h>
#include <iostream>

#include "Cannon.h"

#define CONSOLE_WIDTH 1200
#define CONSOLE_HEIGHT 1200

#define CONSOLE_TITLE L"Fireworks"

#define SET_TEXT_BLUE() SetConsoleTextAttribute(consoleHandle, 1 );
#define SET_TEXT_GREEN() SetConsoleTextAttribute(consoleHandle, 10 );
#define SET_TEXT_PINK() SetConsoleTextAttribute(consoleHandle, 13 );
#define SET_TEXT_RED() SetConsoleTextAttribute(consoleHandle, 12 );
#define SET_TEXT_WHITE() SetConsoleTextAttribute(consoleHandle, 15 );
#define SET_TEXT_YELLOW() SetConsoleTextAttribute(consoleHandle, 14 );


#define CANNON_DISPLAY_SYMBOL '#'


class Console {
public:
	static Console& getInstance() {
		if (!_instance) {
			_instance.reset(new Console());
		}
		return *_instance;
	}

	size_t width() const {
		return innerField.noOfCols;
	}
	size_t height() const {
		return innerField.noOfRows;
	}

	void draw(const Cannon& cannon) const {
		setCoursorToXY(cannon.position());
		std::cout << CANNON_DISPLAY_SYMBOL;
	}
	
	void draw(const Rocket* const obj) const;

	Console(const Console& other) = delete;
	Console(Console&& other) = delete;
	Console operator=(const Console& other) = delete;
	
	virtual ~Console() = default;
protected:
	Console(const int width = CONSOLE_WIDTH, const int height = CONSOLE_HEIGHT) :
		consoleHandle{ setConsoleWindow(width, height) },
		innerField{}
	{};
	struct InnerField {
		InnerField() {
			CONSOLE_SCREEN_BUFFER_INFO consoleBuffer;
			HANDLE consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE) };

			GetConsoleScreenBufferInfo(consoleHandle, &consoleBuffer);
			
			noOfRows = consoleBuffer.srWindow.Bottom - consoleBuffer.srWindow.Top;
			noOfCols = consoleBuffer.srWindow.Right - consoleBuffer.srWindow.Left - 1;
			
		}
		size_t noOfRows;
		size_t noOfCols;
	};

	HANDLE consoleHandle;
	InnerField innerField;
	
	static std::shared_ptr<Console> _instance;
	
	void setCoursorToXY(const Coord& location) const;
	HANDLE setConsoleWindow(const int width, const int height) const;

	void drawProjectile(const Projectile* const obj) const;

	void drawSpark(const FireworkObject* const obj) const;

	void resetPrevLocation(const FireworkObject* const obj) const;

	void drawAtCurLocation(const FireworkObject* const obj) const;

	void eraseObject(const FireworkObject* const obj) const;

	void setColor(eColor curColor) const;

	bool checkCoord(const Coord& location) const;

};


