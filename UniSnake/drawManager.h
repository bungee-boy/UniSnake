#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "IDraw.h"

class DrawManager
{
public:
	void addInterface(IDraw* interface, bool push_front=false);
	void removeInterface(IDraw* interface);
	void update(sf::RenderWindow* window);
private:
	std::vector<IDraw*> m_interfaces;
};