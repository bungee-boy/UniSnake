#pragma once
#include <cmath>
#include <iostream>
#include "inputManager.h"
#include "drawManager.h"
#include "collisionManager.h"
#include "snake.h"
#include "fruit.h"

class Game
{
public:
	Game();
	void begin();
private:
	void addSnake();
	void delSnake(Snake* obj);
	void addFruit();
	void delFruit(Fruit* obj);
	const sf::Vector2u m_screenSize{ 1000, 1000 };  // Screen size
	unsigned int m_fps{ 60 };  // FPS
	sf::RenderWindow* m_window;  // Window (screen)
	DrawManager m_draw;  // Draw manager
	InputManager m_input;  // Input manager
	CollisionManager m_collision;  // Collision manager
	std::vector<Snake*> m_snakes;  // Vector of snakes
	std::vector<Fruit*> m_fruits;  // Vector of foods
	sf::Texture* m_foodTexture1;
	sf::Texture* m_foodTexture2;
};
