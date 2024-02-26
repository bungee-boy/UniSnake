#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

extern const double PI;
extern sf::CircleShape gCircle;
extern const unsigned int gWidth, gHeight;

class snake {
public:
	void update();
	void draw(sf::RenderWindow& window);
private:
	sf::Vector2f vel{ static_cast<float>(gWidth / 2), static_cast<float>(gHeight / 2) };  // Current velocity
	sf::Vector2f vel2{ static_cast<float>(gWidth / 2) - 20, static_cast<float>(gHeight / 2) };  // Current velocity2
	sf::Vector2f vel3{ static_cast<float>(gWidth / 2) - 40, static_cast<float>(gHeight / 2) };  // Current velocity3
	sf::Vector2f vel4{ static_cast<float>(gWidth / 2) - 40, static_cast<float>(gHeight / 2) };  // Current velocity4
	sf::Vector2f vel5{ static_cast<float>(gWidth / 2) - 40, static_cast<float>(gHeight / 2) };  // Current velocity5
	int direction{ 0 };  // Current direction
	int direction2{ 0 };
	int direction3{ 0 };
	int direction4{ 0 };
	int direction5{ 0 };
	int speed{ 1 };  // Movement speed of the snake (update rate)
	int updateCount{ 0 };  // Counter to update
};

