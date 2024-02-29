#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "inputObserver.h"

class inputManager
{
public:
	void registerObserver(inputObserver* observer);
	void update();
private:
	std::vector<inputObserver*> m_observers;
};

