#include "inputManager.h"
#include <iostream>

void inputManager::addInterface(iInput* interface) {
	m_interfaces.push_back(interface);
}

void inputManager::removeInterface(iInput* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void inputManager::update() {
	inputActions action = inputActions::eNone;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		action = inputActions::eP1Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		action = inputActions::eP1Right;

	for (iInput* interface : m_interfaces)
		interface->handleInput(action);
}
