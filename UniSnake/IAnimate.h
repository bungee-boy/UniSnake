#pragma once
#include "SFML\\Graphics.hpp"

class IAnimate {
public:
	virtual void animate() = 0;  // Proccess all animations (MUST not affect any logic!)
protected:
	sf::Clock m_aniClock;
};
