#pragma once
#include "SFML\Graphics.hpp"

class IDraw {
public:
	virtual void draw(sf::RenderWindow* window) = 0;
};
