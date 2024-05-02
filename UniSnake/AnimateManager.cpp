#include "AnimateManager.h"

void AnimateManager::addInterface(IAnimate* interface) {
	m_interfaces.push_back(interface);
}

void AnimateManager::removeInterface(IAnimate* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void AnimateManager::update(sf::RenderWindow* window) {
	for (int i{ 0 }; i < m_interfaces.size(); i++) {
		if (!m_interfaces[i]->m_isAlive)  // If interface is dead
			m_interfaces.erase(m_interfaces.begin() + i);  // Remove interface
	}

	for (int i{ 0 }; i < m_interfaces.size(); i++) {
		m_interfaces[i]->animate(window);
	}
}
