#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include "LinkedList.h"

enum class GameState {
	eMenu,
	eGame
};

class Ui {
public:
	void addText(std::string text, sf::Vector2f pos);
	void update();
private:
	GameState m_gameState{ GameState::eMenu };

	struct TextData {
		sf::Vector2f pos;
		sf::Text text;
	};
	LinkedList<TextData> m_textList;
};

