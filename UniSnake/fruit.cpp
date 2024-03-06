#include "fruit.h"

Fruit::Fruit(int value, sf::Texture* texture, sf::Vector2f pos, CollisionType collision) {
	setCollisionType(collision);
	m_value = value;
	m_texture = *texture;
	m_pos = pos;
	m_sprite = sf::Sprite(m_texture);
	m_sprite.setTexture(m_texture);
	if (getCollisionType() == CollisionType::eCircle)  // Center circle if fruit is round
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setPosition(m_pos);
}

void Fruit::move(float x, float y) {
	m_pos.x += x;
	m_pos.y += y;
	m_sprite.setPosition(m_pos);
}

int Fruit::getValue() {
	return m_value;
}

sf::Vector2f Fruit::getCircleCenter() {
	return m_pos;
}

sf::FloatRect Fruit::getRect() {
	return m_sprite.getGlobalBounds();
}

float Fruit::getRadius() {
	return m_sprite.getLocalBounds().width / 2;
}

bool Fruit::isColliding(ICollision* other) {
	switch (other->getCollisionType()) {
	case CollisionType::eRect:
		break;
	case CollisionType::eCircle: {
		sf::Vector2f offset = getCircleCenter() - other->getCircleCenter();
		float distance = (offset.x * offset.x) + (offset.y * offset.y);  // Offset ^ 2

		float radius = getRadius() + other->getRadius();
		radius *= radius;  // Radius ^ 2

		if (distance <= radius)
			return true;
	}
	}
	return false;
}

void Fruit::collideSnake() {
	m_isAlive = false;
}

void Fruit::collideFruit(int value) {
	m_isAlive = false;
}

void Fruit::draw(sf::RenderWindow* window) {
	window->draw(m_sprite);
}
