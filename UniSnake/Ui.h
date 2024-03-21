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
	bool loadFont(std::string fontName);
	void addText(std::string text, std::string fontName, sf::Vector2f pos, bool center = false);
	void update();
	void draw(sf::RenderWindow* window);
private:
	GameState m_gameState{ GameState::eMenu };
	std::map<std::string, sf::Font> m_fonts;
	struct TextData {
		sf::Vector2f pos;
		sf::Text text;
	};
	LinkedList<TextData> m_textList;
};

