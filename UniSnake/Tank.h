#pragma once
#include "IDraw.h"

class Tank : public IDraw {
public:
	Tank();
	Tank(sf::IntRect size);
	sf::IntRect getSize();
	void draw(sf::RenderWindow* window);
private:
	sf::IntRect m_size;
	unsigned int m_waterLevel{ 0 };
	sf::RectangleShape m_water;
};

