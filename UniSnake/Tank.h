#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"

class Tank {
public:
	Tank(const sf::FloatRect rect);
	sf::FloatRect* getRect();
	void setWaterLevel(float level);
	void drawTank(sf::RenderWindow* window);
	void drawWater(sf::RenderWindow* window);
private:
	static const int TankWidth;
	static const int TankBorder;
	static const sf::Color TankInnerCol;
	static const sf::Color TankOuterCol;
	sf::FloatRect m_rect;
	unsigned int m_waterLevel{ 100 };
	sf::RectangleShape m_tankLeft;
	sf::RectangleShape m_tankRight;
	sf::RectangleShape m_tankBottom;
	sf::RectangleShape m_water;
};

