#include <iostream>
#include "InputManager.h"

void InputManager::addInterface(IInput* interface) {
	m_interfaces.push_back(interface);
}

void InputManager::removeInterface(IInput* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

void InputManager::update() {
	InputActions action = InputActions::eNone;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		action = InputActions::eP1Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		action = InputActions::eP1Right;

	for (IInput* interface : m_interfaces)
		interface->handleInput(action);
}
