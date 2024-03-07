#pragma once
#include <cmath>
#include <iostream>
#include "InputManager.h"
#include "DrawManager.h"
#include "CollisionManager.h"
#include "Tank.h"
#include "Snake.h"
#include "Fruit.h"

enum class GameMode {
	eClassic,
	eArcade
};

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
	unsigned int weightedRand(const std::vector<unsigned int> probabilities);
	const sf::Vector2u m_screenSize{ 1280, 720 };  // Screen size
	unsigned int m_fps{ 60 };  // FPS
	sf::RenderWindow* m_window;  // Window (screen)
	GameMode m_gameMode;  // Game mode
	DrawManager m_draw;  // Draw manager
	InputManager m_input;  // Input manager
	CollisionManager m_collision;  // Collision manager
	Tank m_tank;  // Tank
	std::vector<Snake*> m_snakes;  // Vector of snakes
	std::vector<Fruit*> m_fruits;  // Vector of foods
};
