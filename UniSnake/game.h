#pragma once
#include <cmath>
#include <iostream>
#include "InputManager.h"
#include "DrawManager.h"
#include "AnimateManager.h"
#include "CollisionManager.h"
#include "Ui.h"
#include "Tank.h"
#include "Snake.h"
#include "Fruit.h"

enum class eGameState {
	eMenu,
	eGame
};

class Game
{
public:
	Game();
	void begin();
private:
	enum class eMainMenu {
		eNone,
		eStart,
		eQuit
	};
	void startMenu();
	void startGame();
	void resetSnake(const unsigned int index, const sf::Vector2f pos);
	void killSnake(Snake* obj);
	void resetFruit(const unsigned int index);
	void killFruit(Fruit* obj);
	unsigned int weightedRand(const std::vector<unsigned int> probabilities);
	static const unsigned int MaxSnakes;
	static const unsigned int MaxFruits;
	const sf::Vector2u m_screenSize{ 1280, 720 };  // Screen size
	const sf::Vector2f m_screenSizef{ static_cast<float>(m_screenSize.x), static_cast<float>(m_screenSize.y) };  // Screen size (as float)
	const sf::Vector2f m_screenCenter{ static_cast<float>(m_screenSize.x) / 2.0f, static_cast<float>(m_screenSize.y) / 2.0f };  // Screen center
	unsigned int m_fps{ 120 };  // Frames Per Second (FPS)
	unsigned int m_tps{ 20 };  // Ticks Per Second (TPS)
	unsigned int m_snakeAmount{ 0 };
	unsigned int m_fruitAmount{ 0 };
	eGameState m_gameState{ eGameState::eMenu };  // Game state
	sf::RenderWindow* m_window;  // Window (screen)
	sf::Clock m_ticks;  // Game ticks
	AnimateManager m_ani;  // Animation manager
	DrawManager m_draw;  // Draw manager
	InputManager m_input;  // Input manager
	CollisionManager m_collision;  // Collision manager
	Ui m_ui;  // User Interface
	Tank* m_tank;  // Tank
	Snake* m_snakes[2];  // Array of snakes
	Fruit* m_fruits[5];  // Array of foods
};
