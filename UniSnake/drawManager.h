#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "iDraw.h"

class drawManager
{
public:
	void addInterface(iDraw* interface);
	void removeInterface(iDraw* interface);
	void update(sf::RenderWindow* window);
private:
	std::vector<iDraw*> m_interfaces;
};