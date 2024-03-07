#include "Tank.h"

Tank::Tank() {

}

Tank::Tank(sf::IntRect size) {
	m_size = size;
	m_water.setFillColor({ 50, 50, 255, 100 });
}

sf::IntRect Tank::getSize() {
	return m_size;
}

void Tank::draw(sf::RenderWindow* window) {
	window->draw(m_water);
}
