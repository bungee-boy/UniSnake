#include "inputManager.h"

void inputManager::registerObserver(inputObserver* observer) {
	m_observers.push_back(observer);
}

void inputManager::update() {
	inputActions action = inputActions::eNone;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		action = inputActions::eP1Left;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		action = inputActions::eP1Right;

	if (action != inputActions::eNone) {
		for (inputObserver* observer : m_observers)
			observer->handleInput(action);
	}
}
