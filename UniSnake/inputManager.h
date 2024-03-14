#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "IInput.h"

class InputManager
{
public:
	void addInterface(IInput* interface);
	void removeInterface(IInput* interface);
	bool setP1Controller(const int& joystickIndex);
	bool setP2Controller(const int& joystickIndex);
	void update();
private:
	std::vector<IInput*> m_interfaces;
	int m_p1ControllerIndex{ -1 };
	int m_p2ControllerIndex{ -1 };
};

