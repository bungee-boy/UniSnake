#include "collisionManager.h"

void collisionManager::addInterface(iCollision* interface) {
	m_interfaces.push_back(interface);
}

void collisionManager::removeInterface(iCollision* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void collisionManager::checkCollision(iCollision* current, iCollision* other) {
	if (current->isColliding(other)) {
		if (dynamic_cast<snake*>(other) != nullptr) {
			current->collideSnake();
		}
		else if (dynamic_cast<fruit*>(other) != nullptr) {
			current->collideFruit(static_cast<fruit*>(other)->getValue());
		}
	}
}

void collisionManager::update() {
	for (int current{ 0 }; current < m_interfaces.size(); current++) {
		for (int other{ 0 }; other < m_interfaces.size(); other++) {
			if (current != other) {
				checkCollision(m_interfaces[current], m_interfaces[other]);
				checkCollision(m_interfaces[other], m_interfaces[current]);
			}
		}
	}
}
