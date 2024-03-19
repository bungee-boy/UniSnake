#include "Fruit.h"

const std::vector<unsigned int> Fruit::Probabilities{ 4, 3, 2, 1 };  // Probabilities of values
sf::Texture Fruit::TextureTwo;
sf::Texture Fruit::TextureThree;
sf::Texture Fruit::TextureFour;
sf::Texture Fruit::TextureFive;

Fruit::Fruit(unsigned int value, sf::FloatRect screenBounds, CollisionType collision) {
	setCollisionType(collision);
	m_value = value;
	switch (m_value) {
	case 2:
		m_sprite = sf::Sprite(TextureTwo);
		break;
	case 3:
		m_sprite = sf::Sprite(TextureThree);
		break;
	case 4:
		m_sprite = sf::Sprite(TextureFour);
		break;
	case 5:
		m_sprite = sf::Sprite(TextureFive);
		break;
	default:
		std::cerr << "Fruit value is out of range 2->5 ! (m_value: " << m_value << ")\n";
	}

	m_pos.x = (rand() % static_cast<int>((screenBounds.width - m_sprite.getLocalBounds().width))) + screenBounds.left;  // Bound to width + offset
	m_pos.y = (rand() % static_cast<int>((screenBounds.height - m_sprite.getLocalBounds().height))) + screenBounds.top;  // Bound to height + offset

	if (getCollisionType() == CollisionType::eCircle) {  // Center circle if fruit is round
		m_pos.x += m_sprite.getLocalBounds().width / 2;  // Offset position to visually stay
		m_pos.y += m_sprite.getLocalBounds().height / 2;
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	}
	m_sprite.setPosition(m_pos);
}

void Fruit::loadTextures() {
	if (!TextureTwo.loadFromFile("textures\\two.png"))  // Textures::two
		std::cerr << "Failed to load two.png" << '\n';
	if (!TextureThree.loadFromFile("textures\\three.png"))  // Textures::three
		std::cerr << "Failed to load three.png" << '\n';
	if (!TextureFour.loadFromFile("textures\\four.png"))  // Textures::four
		std::cerr << "Failed to load four.png" << '\n';
	if (!TextureFive.loadFromFile("textures\\five.png"))  // Textures::five
		std::cerr << "Failed to load five.png" << '\n';
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

void Fruit::collideFruit(int value) {
	m_isAlive = false;
}

void Fruit::draw(sf::RenderWindow* window) {
	window->draw(m_sprite);
}
