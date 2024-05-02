#include "DrawManager.h"

void DrawManager::addInterface(IDraw* interface, bool push_front) {
	if (push_front)
		m_interfaces.insert(m_interfaces.begin(), interface);
	else
		m_interfaces.push_back(interface);
}

void DrawManager::removeInterface(IDraw* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void DrawManager::update(sf::RenderWindow* window) {
	for (int i{ 0 }; i < m_interfaces.size(); i++) {
		if (!m_interfaces[i]->m_isAlive)  // If interface is dead
			m_interfaces.erase(m_interfaces.begin() + i);  // Remove interface
	}

	for (IDraw* interface : m_interfaces)
		interface->draw(window);
}
