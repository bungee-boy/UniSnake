#pragma once
#include "SFML\Graphics.hpp"

class IDraw {
public:
	bool m_isAlive{ true };
	virtual void draw(sf::RenderWindow* window) = 0;
private:
	unsigned int m_drawPriority{ 0 };  // 0 = None, 1 = Highest, 99... = Lowest
};
