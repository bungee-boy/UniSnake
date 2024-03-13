#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Tank {
public:
	Tank(const sf::FloatRect rect);
	sf::FloatRect getRect();
	sf::FloatRect getWaterRect();
	void drawTank(sf::RenderWindow* window);
	void drawWater(sf::RenderWindow* window);
private:
	static const int TankWidth;
	static const int TankBorder;
	sf::FloatRect m_rect;
	unsigned int m_waterLevel{ 0 };
	sf::RectangleShape m_tankLeft;
	sf::RectangleShape m_tankRight;
	sf::RectangleShape m_tankBottom;
	sf::RectangleShape m_water;
};

