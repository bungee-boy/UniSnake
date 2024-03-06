#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "iInput.h"

class inputManager
{
public:
	void addInterface(iInput* interface);
	void update();
private:
	std::vector<iInput*> m_interfaces;
};

