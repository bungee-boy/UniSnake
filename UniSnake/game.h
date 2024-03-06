#pragma once
#include <cmath>
#include <iostream>
#include "inputManager.h"
#include "drawManager.h"
#include "collisionManager.h"
#include "snake.h"
#include "fruit.h"

class game
{
public:
	game();
	void begin();
private:
	void addSnake();
	void delSnake(snake* obj);
	void addFruit();
	void delFruit(fruit* obj);
	const sf::Vector2u m_screenSize{ 1000, 1000 };  // Screen size
	unsigned int m_fps{ 60 };  // FPS
	sf::RectangleShape m_rect;  // Load rect class
	sf::CircleShape m_circle;  // Load circle class
	sf::RenderWindow* m_window;  // Window (screen)
	drawManager m_draw;  // Draw manager
	inputManager m_input;  // Input manager
	collisionManager m_collision;  // Collision manager
	std::vector<snake*> m_snakes;  // Vector of snakes
	std::vector<fruit*> m_fruits;  // Vector of foods
	sf::Texture* m_foodTexture1;
	sf::Texture* m_foodTexture2;
};
