#include "Tank.h"

const int Tank::TankWidth{ 8 };
const int Tank::TankBorder{ 3 };
const sf::Color Tank::TankInnerCol{ 150, 150, 150, 255 };
const sf::Color Tank::TankOuterCol{ 50, 50, 50, 255 };

Tank::Tank(const sf::FloatRect rect) {
	m_rect = rect;

	m_tankLeft.setOutlineThickness(-TankBorder);  // n to the inside
	m_tankRight.setOutlineThickness(-TankBorder);
	m_tankBottom.setOutlineThickness(-TankBorder);

	m_tankLeft.setFillColor(TankInnerCol);  // Set colour for borders
	m_tankLeft.setOutlineColor(TankOuterCol);
	m_tankRight.setFillColor(TankInnerCol);
	m_tankRight.setOutlineColor(TankOuterCol);
	m_tankBottom.setFillColor(TankInnerCol);
	m_tankBottom.setOutlineColor(TankOuterCol);

	m_tankLeft.setSize({ TankWidth, m_rect.height });  // Sides
	m_tankRight.setSize({ TankWidth, m_rect.height });
	m_tankBottom.setSize({ m_rect.width, TankWidth });  // bottom

	m_tankLeft.setPosition({ m_rect.left, m_rect.top });  // Left
	m_tankRight.setPosition({ m_rect.left + m_rect.width - TankWidth, m_rect.top });  // Right
	m_tankBottom.setPosition({ m_rect.left, m_rect.top + m_rect.height - TankWidth });  // Bottom

	m_water.setPosition({ m_rect.left + TankWidth, m_rect.top });
	m_water.setSize({ m_rect.width - (TankWidth * 2), m_rect.height - TankWidth});
	m_water.setFillColor({ 50, 50, 255, 50 });
}

sf::FloatRect Tank::getWaterRect() {
	return m_water.getGlobalBounds();
}

sf::FloatRect Tank::getRect() {
	return m_rect;
}

void Tank::setWaterLevel(unsigned int level) {
	m_water.setPosition({ m_water.getPosition().x, m_tankLeft.getPosition().y + (100 - level)});
}

void Tank::drawTank(sf::RenderWindow* window) {
	window->draw(m_tankLeft);
	window->draw(m_tankRight);
	window->draw(m_tankBottom);
}

void Tank::drawWater(sf::RenderWindow* window) {
	window->draw(m_water);
}
