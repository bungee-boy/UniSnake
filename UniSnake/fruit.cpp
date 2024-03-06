#include "fruit.h"

fruit::fruit(int value, sf::Texture texture, sf::Vector2f pos, collisionType collision) {
	setCollisionType(collision);
	m_value = value;
	m_texture = texture;
	m_pos = pos;
	m_sprite = sf::Sprite(m_texture);
	m_sprite.setTexture(m_texture);
	if (getCollisionType() == collisionType::eCircle)  // Center circle if fruit is round
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_pos);
}

void fruit::move(float x, float y) {
	m_pos.x += x;
	m_pos.y += y;
	m_sprite.setPosition(m_pos);
}

int fruit::getValue() {
	return m_value;
}

sf::Vector2f fruit::getCircleCenter() {
	return m_pos;
}

sf::FloatRect fruit::getRect() {
	return m_sprite.getGlobalBounds();
}

float fruit::getRadius() {
	return m_sprite.getLocalBounds().width / 2;
}

bool fruit::isColliding(iCollision* other) {
	switch (other->getCollisionType()) {
	case collisionType::eRect:
		break;
	case collisionType::eCircle: {
		sf::Vector2f offset = getCircleCenter() - other->getCircleCenter();
		float distance = (offset.x * offset.x) + (offset.y * offset.y);  // Offset ^ 2

		float radius = getRadius() + other->getRadius();
		radius *= radius;  // Radius ^ 2

		//std::cout << getCircleCenter().x << ',' << getCircleCenter().y << ' ' << other->getCircleCenter().x << ',' << other->getCircleCenter().y << '\n';
		if (distance <= radius)
			return true;
	}
	}
	return false;
}

void fruit::collideSnake() {
	std::cout << "Fruit -> collidedSnake()\n";
	m_isAlive = false;
}

void fruit::collideFruit(int value) {
	std::cout << "Fruit -> collidedFruit(" << value << ")\n";
}

void fruit::draw(sf::RenderWindow* window) {
	window->draw(m_sprite);
}
