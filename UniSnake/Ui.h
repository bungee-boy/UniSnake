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
	sf::Text* addText(const std::string text, const std::string fontName, const sf::Vector2f pos, const bool center = true, const unsigned int size = 30, const unsigned int style = 0);
	void clearTexts();
	sf::FloatRect addRect(const sf::Vector2f pos, const sf::Vector2f size, const sf::Color fillColour, const sf::Color outlineColour = { 0, 0, 0, 0 }, const float thickness = 0.0f);
	sf::FloatRect addLineX(const sf::Vector2f startPos, const unsigned int xSize, const sf::Color fillColour = RectInnerCol, const sf::Color outlineColour = RectOuterCol);
	sf::FloatRect addLineY(const sf::Vector2f startPos, const unsigned int ySize, const sf::Color fillColour = RectInnerCol, const sf::Color outlineColour = RectOuterCol);
	void clearRects();
	bool loadTexture(const std::string textureName);
	void unloadTextures();
	sf::FloatRect addRectTexture(const std::string textureName, const sf::Vector2f pos, const sf::Vector2f size, const float rotation = 0.0f, const bool center = true);
	void clearAll();
	void update();
	void draw(sf::RenderWindow* window);
private:
	GameState m_gameState{ GameState::eMenu };
	std::map<std::string, sf::Font> m_fonts;
	std::map<std::string, sf::Texture*> m_textures;
	LinkedList<sf::Text*> m_textList;
	LinkedList<sf::RectangleShape*> m_rectList;
};

