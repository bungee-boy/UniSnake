#include "Tank.h"

const int Tank::TankWidth{ 8 };
const int Tank::TankBorder{ 3 };
const sf::Color Tank::TankInnerCol{ 150, 150, 150, 255 };
const sf::Color Tank::TankOuterCol{ 60, 60, 60, 255 };
const sf::Color Tank::WaterCol{ 36, 103, 237, 80 };

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

	m_water.setPosition({ m_rect.left + TankWidth, m_rect.top });  // Water
	m_water.setSize({ m_rect.width - (TankWidth * 2), m_rect.height - TankWidth});
	m_water.setFillColor(WaterCol);
	m_rect = sf::FloatRect({ m_rect.left + TankWidth - 2, m_rect.top, m_rect.width - (TankWidth * 2) + 4, m_rect.height - TankWidth + 2 });  // Match collision to water
}

sf::FloatRect* Tank::getRect() {
	return &m_rect;
}

void Tank::setWaterLevel(float level) {
	if (level > 100) {
		level = 100;
		std::cerr << "Error -> Tank::setWaterLevel(level): Water level was out of range! (level > 100)\n";
	}
	else if (level < 0) {
		level = 0;
		std::cerr << "Error -> Tank::setWaterLevel(level): Water level was out of range! (level < 0)\n";
	}
	m_water.setPosition({ m_water.getPosition().x, m_tankLeft.getPosition().y + (m_tankLeft.getSize().y * ((100 - level) / 100))});
	m_water.setSize({ m_water.getSize().x, m_tankLeft.getSize().y * (level / 100) - TankWidth });
	if (m_water.getSize().y < 0)
		m_water.setSize({ m_water.getSize().x, 0 });

	m_rect.top = m_water.getPosition().y;  // Ensure collision rect matches visual rect
	m_rect.height = m_water.getSize().y;
}

void Tank::drawTank(sf::RenderWindow* window) {
	window->draw(m_tankLeft);
	window->draw(m_tankRight);
	window->draw(m_tankBottom);
}

void Tank::drawWater(sf::RenderWindow* window) {
	window->draw(m_water);
}
