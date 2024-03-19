#pragma once
#include <vector>
#include "SFML\Graphics.hpp"

enum class GameState {
	eMenu,
	eGame
};

class Ui {
public:
private:
	GameState m_gameState{ GameState::eMenu };
	//sf::Text
};

