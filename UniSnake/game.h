#pragma once
#include <cmath>
#include <iostream>
#include "inputManager.h"
#include "snake.h"

class game
{
public:
	void begin();
private:
	const sf::Vector2u m_screenSize{ 1000, 1000 };  // Screen size
	unsigned int m_fps{ 60 };  // FPS
	sf::RectangleShape m_rect;  // Load rect class
	sf::CircleShape m_circle;  // Load circle class
	sf::RenderWindow* m_window;  // Window (screen)
};

