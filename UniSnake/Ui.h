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
	void addText(const std::string text, const std::string fontName, const sf::Vector2f pos, const bool center = false, const unsigned int size = 30);
	void clearText();
	void addRect(const sf::Vector2f pos, const sf::Vector2f size, const sf::Color fillColour, const sf::Color outlineColour = { 0, 0, 0, 0 }, const float thickness = 0.0f);
	void clearRect();
	void update();
	void draw(sf::RenderWindow* window);
private:
	GameState m_gameState{ GameState::eMenu };
	std::map<std::string, sf::Font> m_fonts;
	LinkedList<sf::Text*> m_textList;
	LinkedList<sf::RectangleShape*> m_rectList;
};

