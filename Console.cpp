#include "Console.h"

std::shared_ptr<Console> Console::_instance{};

HANDLE Console::setConsoleWindow(const int width, const int height) const
{
	SetConsoleTitle(CONSOLE_TITLE);

	HANDLE consoleHandle{ GetStdHandle(STD_OUTPUT_HANDLE)};
	HWND console = GetConsoleWindow();

	CONSOLE_CURSOR_INFO coursor;
	coursor.dwSize = 16;
	coursor.bVisible = FALSE;

	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SetWindowLong(console, GWL_STYLE, GetWindowLong(console, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

	SetConsoleCursorInfo(consoleHandle, &coursor);
	
	return consoleHandle;
}

void Console::setCoursorToXY(const Coord& location) const {
	COORD position;
	position.X = location._posX;
	position.Y = location._posY;
	SetConsoleCursorPosition(consoleHandle, position);
}

void Console::draw(const Rocket* const obj) const {

	if (obj->isDetonated() == false) {
		if (obj->curLocation() != obj->prevLocation()) {
			resetPrevLocation(obj);
			drawAtCurLocation(obj);
		}
	}
	else {
		eraseObject(obj);
		for (const auto& elem : obj->fireCrackers()) {
			const Projectile* temp{ dynamic_cast<const Projectile*>(elem.get()) };
			if (temp) {
				drawProjectile(temp);
			}
			else {
				drawSpark(elem.get());
			}
		}
	}
}

void Console::drawProjectile(const Projectile* const obj) const {
	
	if (obj->isDetonated() == false) {
		if (obj->curLocation() != obj->prevLocation()) {
			resetPrevLocation(obj);
			drawAtCurLocation(obj);
		}
	}
	else {
		eraseObject(obj);
		for (const auto& elem : obj->fireCrackers()) {
			drawSpark(elem.get());
		}
	}
}

void Console::drawSpark(const FireworkObject* const obj) const {
	
	if (!obj->isEpxloded()) {
		if (obj->curLocation() != obj->prevLocation()) {
			resetPrevLocation(obj);
			drawAtCurLocation(obj);
		}
	}
	else {
		eraseObject(obj);
	}
}

void Console::resetPrevLocation(const FireworkObject* const obj) const {
	Coord prevLocation{ obj->prevLocation() };
	if (checkCoord(prevLocation)) {
		setCoursorToXY(prevLocation);
		std::cout << " ";
	}
}

void Console::drawAtCurLocation(const FireworkObject* const obj) const {
	Coord curLocation{ obj->curLocation() };
	if (checkCoord(curLocation)) {
		setCoursorToXY(curLocation);
		setColor(obj->color());
		std::cout << obj->dispalySymbol();
		setColor(eColor::WHITE);
	}
}

void Console::eraseObject(const FireworkObject* const obj) const {
	Coord curLocation{ obj->curLocation() };
	if (checkCoord(curLocation))
	{
		setCoursorToXY(curLocation);
		std::cout << " ";
	}
}

void Console::setColor(eColor curColor) const {
	switch (curColor) {
	case eColor::BLUE:
		SET_TEXT_BLUE();
		break;
	case eColor::GREEN:
		SET_TEXT_GREEN();
		break;
	case eColor::PINK:
		SET_TEXT_PINK();
		break;
	case eColor::RED:
		SET_TEXT_RED();
		break;
	case eColor::WHITE:
		SET_TEXT_WHITE();
		break;
	case eColor::YELLOW:
		SET_TEXT_YELLOW();
		break;
	}
}

bool Console::checkCoord(const Coord& location) const {
	return location._posX < innerField.noOfCols&& location._posY >= 1 && location._posY < innerField.noOfRows;
}
