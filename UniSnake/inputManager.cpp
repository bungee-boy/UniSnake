#include <iostream>
#include "InputManager.h"

const float InputManager::DeadZone{ 20.0f };

void InputManager::addInterface(IInput* interface) {
	m_interfaces.push_back(interface);
}

void InputManager::removeInterface(IInput* interface) {
	m_interfaces.erase(std::find(m_interfaces.begin(), m_interfaces.end(), interface));
}

bool InputManager::setP1Controller(const int& joystickIndex) {
	sf::Joystick::update();  // Ensure data is current (only updates in eventloop)
	if (joystickIndex == -1) {  // No controller
		m_p1ControllerIndex = joystickIndex;
		return true;
	}
	else if (sf::Joystick::isConnected(joystickIndex) && sf::Joystick::hasAxis(joystickIndex, sf::Joystick::Z) && joystickIndex != m_p2ControllerIndex) {
		m_p1ControllerIndex = joystickIndex;
		return true;
	}
	else {  // Controller is not valid
		m_p1ControllerIndex = -1;
		std::cerr << "InputManager::setP1Controller(joystickIndex) -> Index was not valid or in use!\n";
		return false;
	}
}

bool InputManager::setP2Controller(const int& joystickIndex) {
	sf::Joystick::update();  // Ensure data is current (only updates in eventloop)
	if (joystickIndex == -1) {  // No controller
		m_p2ControllerIndex = joystickIndex;
		return true;
	}
	else if (sf::Joystick::isConnected(joystickIndex) && sf::Joystick::hasAxis(joystickIndex, sf::Joystick::X) && joystickIndex != m_p2ControllerIndex) {
		m_p2ControllerIndex = joystickIndex;
		return true;
	}
	else {  // Controller is not valid
		m_p2ControllerIndex = -1;
		std::cerr << "InputManager::setP1Controller(joystickIndex) -> Index was not valid or in use!\n";
		return false;
	}
}

void InputManager::update() {
	// Player 1
	InputActions action = InputActions::eNone;
	float data = 0.0f;
	if (m_p1ControllerIndex == -1) {  // P1 Keyboard
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			action = InputActions::eP1Left;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			action = InputActions::eP1Right;
	}
	else {  // P1 Controller
		data = sf::Joystick::getAxisPosition(m_p1ControllerIndex, sf::Joystick::X);
		if (data < -DeadZone)
			action = InputActions::eP1Left;
		else if (data > DeadZone)
			action = InputActions::eP1Right;
		if (action == InputActions::eNone)
			data = 0.0f;
	}

	if (action != InputActions::eNone) {  // Update entities
		std::cout << static_cast<int>(action) << ' ' << data << ' ' << m_p1ControllerIndex << '\n';
		for (IInput* interface : m_interfaces)
				interface->handleInput(action, data);
	}
	
}
