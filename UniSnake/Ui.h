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
	void loadFont(sf::Font font);
	void addText(std::string text, sf::Vector2f pos, sf::Color colour);
	void update();
private:
	GameState m_gameState{ GameState::eMenu };
	std::map<std::string, sf::Font> m_fonts;
	struct TextData {
		sf::Vector2f pos;
		sf::Text text;
	};
	LinkedList<TextData> m_textList;
};

