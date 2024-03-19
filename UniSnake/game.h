#pragma once
#include <cmath>
#include <iostream>
#include "InputManager.h"
#include "DrawManager.h"
#include "CollisionManager.h"
#include "Tank.h"
#include "Snake.h"
#include "Fruit.h"

class Game
{
public:
	Game();
	void begin();
private:
	void startGame();
	void addSnake();
	void delSnake(Snake* obj);
	void addFruit();
	void delFruit(Fruit* obj);
	unsigned int weightedRand(const std::vector<unsigned int> probabilities);
	const sf::Vector2u m_screenSize{ 1280, 720 };  // Screen size
	unsigned int m_fps{ 60 };  // Frames Per Second (FPS)
	unsigned int m_tps{ 25 };  // Ticks Per Second (TPS)
	sf::RenderWindow* m_window;  // Window (screen)
	sf::Clock m_ticks;  // Game ticks
	DrawManager m_draw;  // Draw manager
	InputManager m_input;  // Input manager
	CollisionManager m_collision;  // Collision manager
	Tank* m_tank;  // Tank
	std::vector<Snake*> m_snakes;  // Vector of snakes
	std::vector<Fruit*> m_fruits;  // Vector of foods
};
