#pragma once
#include "SFML\Graphics.hpp"

class iDraw {
public:
	virtual void draw(sf::RenderWindow* window) = 0;
};
