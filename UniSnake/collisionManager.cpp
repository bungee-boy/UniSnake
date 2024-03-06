#include "CollisionManager.h"

void CollisionManager::addInterface(ICollision* interface) {
	m_interfaces.push_back(interface);
}

void CollisionManager::removeInterface(ICollision* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void CollisionManager::checkCollision(ICollision* current, ICollision* other) {
	if (current->isColliding(other)) {
		if (dynamic_cast<Snake*>(other) != nullptr)
			current->collideSnake();
		else if (dynamic_cast<Fruit*>(other) != nullptr) {
			current->collideFruit(static_cast<Fruit*>(other)->getValue());
			static_cast<Fruit*>(other)->m_isAlive = false;
		}
	}
}

void CollisionManager::update() {
	for (int current{ 0 }; current < m_interfaces.size(); current++) {
		for (int other{ 0 }; other < m_interfaces.size(); other++) {
			if (current != other)
				checkCollision(m_interfaces[current], m_interfaces[other]);
		}
	}
}
