#pragma once
#include "SFML\\Graphics.hpp"

class IAnimate {
public:
	bool m_isAlive{ true };
	virtual void animate(sf::RenderWindow* window) = 0;  // Proccess all animations (MUST not affect any logic!)
protected:
	sf::Clock m_aniClock;
};
