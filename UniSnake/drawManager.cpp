#include "drawManager.h"

void drawManager::addInterface(iDraw* interface) {
	m_interfaces.push_back(interface);
}

void drawManager::removeInterface(iDraw* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void drawManager::update(sf::RenderWindow* window) {
	for (iDraw* interface : m_interfaces)
		interface->draw(window);
}
