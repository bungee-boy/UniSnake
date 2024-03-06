#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "iDraw.h"

class DrawManager
{
public:
	void addInterface(IDraw* interface);
	void removeInterface(IDraw* interface);
	void update(sf::RenderWindow* window);
private:
	std::vector<IDraw*> m_interfaces;
};