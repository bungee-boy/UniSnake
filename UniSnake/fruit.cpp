#include "Fruit.h"

const std::vector<unsigned int> Fruit::Probabilities{ 4, 3, 2, 1 };  // Probabilities of values
sf::Texture Fruit::Texture[4]{ sf::Texture(), sf::Texture(), sf::Texture(), sf::Texture() };

Fruit::Fruit() {

}

Fruit::Fruit(unsigned int value, sf::FloatRect* tank, CollisionType collision) {
	m_sprite = sf::Sprite();
	init(value, tank, collision);
}

void Fruit::init(unsigned int value, sf::FloatRect* tank, CollisionType collision) {
	m_isAlive = true;
	m_isRegistered = false;
	setCollisionType(collision);
	m_tank = tank;
	m_value = value;
	if (m_value >= 2 && m_value <= 5)  // Ensure value is in range
		m_sprite = sf::Sprite(Texture[m_value - 2]);
	else
		std::cerr << "Fruit value is out of range 2 - 5 ! (m_value: " << m_value << ")\n";

	m_pos.x = (rand() % static_cast<int>((m_tank->width - m_sprite.getGlobalBounds().width))) + m_tank->left;  // Bound to width + offset
	m_pos.y = (rand() % static_cast<int>((m_tank->height - m_sprite.getGlobalBounds().height))) + m_tank->top;  // Bound to height + offset

	if (getCollisionType() == CollisionType::eCircle) {  // Center circle if fruit is round
		m_pos.x += m_sprite.getGlobalBounds().width / 2;  // Offset position to visually stay
		m_pos.y += m_sprite.getGlobalBounds().height / 2;
		m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2, m_sprite.getGlobalBounds().height / 2);
	}
	m_sprite.setPosition(m_pos);
}

void Fruit::loadTextures() {
	for (int i{ 2 }; i <= 5; i++) {
		std::cout << "Loaded texture " << i << '\n';
		if (!Fruit::Texture[0].loadFromFile("textures\\fruit_" + std::to_string(i) + ".png"))  // Load textures (2 -> 5)
			std::cerr << "Failed to load fruit_" << i << ".png" << '\n';
	}
}

void Fruit::setPos(const sf::Vector2f newPos) {
	m_pos = newPos;
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

bool Fruit::isColliding(ICollision& other) {
	switch (other.getCollisionType()) {
	case CollisionType::eRect:
		break;
	case CollisionType::eCircle: {
		sf::Vector2f offset = getCircleCenter() - other.getCircleCenter();
		float distance = (offset.x * offset.x) + (offset.y * offset.y);  // Offset ^ 2

		float radius = getRadius() + other.getRadius();
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

void Fruit::collideFruit(const int value) {
	m_isAlive = false;
}

void Fruit::update() {
	if (m_tank != nullptr) {
		if (m_pos.y < m_tank->top)  // Move fruit down with water
			setPos({ m_pos.x, m_tank->top });
	}
}

void Fruit::animate(sf::RenderWindow* window) {
	if (m_aniClock.getElapsedTime() >= sf::milliseconds(250)) {
		if (m_aniOffset == -4 || m_aniOffset == 4)
			m_aniDir = !m_aniDir;
		if (m_aniDir)
			m_aniOffset += 2;
		else
			m_aniOffset -= 2;
		m_sprite.setPosition({ m_pos.x, m_pos.y + m_aniOffset });
		m_aniClock.restart();
	}
}

void Fruit::draw(sf::RenderWindow* window) {
	window->draw(m_sprite);
	sf::RectangleShape rect = sf::RectangleShape({ 10, 10 });
	rect.setOrigin({ 5, 5 });
	rect.setPosition(m_pos);
	window->draw(rect);
}
