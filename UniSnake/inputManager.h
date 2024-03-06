#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "iInput.h"

class InputManager
{
public:
	void addInterface(IInput* interface);
	void removeInterface(IInput* interface);
	void update();
private:
	std::vector<IInput*> m_interfaces;
};

