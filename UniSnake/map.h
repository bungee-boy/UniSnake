#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

extern sf::RectangleShape gRect;
extern sf::CircleShape gCircle;

class Map {
public:
	static const unsigned int m_width{ 20 }, m_height{ 20 };

	Map();
	Map(const sf::Vector2u& windowSize);

	const sf::Vector2u getCellSize() const;
	const bool getCell(const sf::Vector2i& gridPos) const;

	void setCellSize(const sf::Vector2u& windowSize);
	void setCell(const sf::Vector2i& gridPos, const bool& state);

	sf::Vector2i convertToGrid(const sf::Vector2i& screenPos);

	void clear();
	void iterate(const unsigned int times = 1);
	void draw(sf::RenderWindow& window);

private:
	sf::Vector2i m_cellSize{ 0, 0 };

	bool m_map[m_height][m_width];
};
