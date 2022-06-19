#pragma once
#include "Console.h"

class Simulator
{
public:
	static Simulator& getInstance() {
		if (!_instance) {
			_instance.reset(new Simulator());
		}
		return *_instance;
	}

	void run() {
		Coord cannonPos{ _console.width() / 2, _console.height() };

		_cannon.setPosition(cannonPos);
		_console.draw(_cannon);
		
		while (1) {
			std::shared_ptr<Rocket> rocket{ _cannon.load() };

			rocket->launch();

			while (!rocket->isEpxloded()) {
				rocket->fly();
				_console.draw(rocket.get());
			}
		}
	}

	Simulator(const Simulator& other) = delete;
	Simulator(Simulator&& other) = delete;
	Simulator operator=(const Simulator& other) = delete;

	~Simulator() = default;
private:
	Simulator() :
		_cannon{ Cannon::getInstance() },
		_console{ Console::getInstance() }
	{}
	static std::shared_ptr<Simulator> _instance;
	Cannon& _cannon;
	Console& _console;
};
