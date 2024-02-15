#include "map.h"

sf::Color gWhite{ 50, 255, 25 };

Map::Map() {
	gRect.setFillColor(gWhite);
	clear();
}

Map::Map(const sf::Vector2u& windowSize) {
	setCellSize(windowSize);
	gRect.setFillColor(gWhite);
	clear();
}

const sf::Vector2u Map::getCellSize() const {
	return static_cast<sf::Vector2u>(m_cellSize);
};

const bool Map::getCell(const sf::Vector2i& gridPos) const {
	int x{ gridPos.x }, y{ gridPos.y };
	if (x < 0)
		x += m_width - 1;
	if (x >= m_width)
		x -= m_width;
	if (y < 0)
		y += m_height - 1;
	if (y >= m_height)
		y -= m_height;
	return m_map[y][x];
}

void Map::setCellSize(const sf::Vector2u& windowSize) {
	m_cellSize.x = windowSize.x / m_width;
	m_cellSize.y = windowSize.y / m_height;
	gRect.setSize({ static_cast<float>(m_cellSize.x), static_cast<float>(m_cellSize.y) });
}

void Map::setCell(const sf::Vector2i& gridPos, const bool& state) {
	int x{ gridPos.x }, y{ gridPos.y };
	if (x < 0)
		x += m_width - 1;
	if (x >= m_width)
		x -= m_width;
	if (y < 0)
		y += m_height - 1;
	if (y >= m_height)
		y -= m_height;
	m_map[y][x] = state;
}

sf::Vector2i Map::convertToGrid(const sf::Vector2i& screenPos) {
	return sf::Vector2i({ screenPos.x / m_cellSize.x, screenPos.y / m_cellSize.y });
}

void Map::clear() {  // Clear map
	memset(m_map, 0, (m_height * m_width) * sizeof(bool));
}

void Map::iterate(const unsigned int times) {
}

void Map::draw(sf::RenderWindow& window) {
	for (unsigned int y{ 0 }; y < m_height; y++) {  // Draw cells
		for (unsigned int x{ 0 }; x < m_width; x++) {
			if (m_map[y][x]) {
				gRect.setPosition(static_cast<float>(x * m_cellSize.x), static_cast<float>(y * m_cellSize.y));
				window.draw(gRect);
			}
		}
	}
}
