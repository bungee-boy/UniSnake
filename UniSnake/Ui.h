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
	static const int RectWidth;
	static const int RectBorder;
	static const sf::Color RectInnerCol;
	static const sf::Color RectOuterCol;
	bool loadFont(std::string fontName);
	void unloadFonts();
	void addText(const std::string text, const std::string fontName, const sf::Vector2f pos, const bool center = false, const unsigned int size = 30, const unsigned int style = 0);
	void clearTexts();
	void addRect(const sf::Vector2f pos, const sf::Vector2f size, const sf::Color fillColour, const sf::Color outlineColour = { 0, 0, 0, 0 }, const float thickness = 0.0f);
	void addLineX(const sf::Vector2f startPos, const unsigned int xSize);
	void addLineY(const sf::Vector2f startPos, const unsigned int ySize);
	void clearRects();
	bool loadTexture(std::string texture);
	void unloadTextures();
	void addRectTexture(const std::string texture, const sf::Vector2f pos, const sf::Vector2f size);
	void update();
	void draw(sf::RenderWindow* window);
private:
	GameState m_gameState{ GameState::eMenu };
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::Texture*> m_textures;
	LinkedList<sf::Text*> m_textList;
	LinkedList<sf::RectangleShape*> m_rectList;
};

