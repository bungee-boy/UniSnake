#include "Game.h"

Game::Game() {
	srand(static_cast<unsigned int>(time(NULL)));
	sf::ContextSettings settings;  // Setup window settings
	settings.antialiasingLevel = 8;

	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Water Snakes - D3169324", sf::Style::Default, settings);  // Create window
	m_window->setFramerateLimit(m_fps);  // Set target framerate

	m_tank = new Tank({ 40, 40, static_cast<float>(m_screenSize.x - 330), static_cast<float>(m_screenSize.y - 60) });

	Fruit::loadTextures();  // Load fruit textures
}

void Game::begin() {
	//std::cout << m_input.setP1Controller(0) << '\n';  // Controller debugging
	while (m_window->isOpen()) {  // Main loop
		switch (m_gameState) {
		case eGameState::eMenu:
			startMenu();
			break;
		case eGameState::eGame:
			addSnake();
			startGame();
			break;
		}
	}
}

void Game::startMenu() {
	m_ui.clearAll();

	sf::Text* tempRect = m_ui.addText("Water Snakes", "title", { m_screenCenter.x, 40 }, true, 50, sf::Text::Underlined);
	m_ui.addLineX({ tempRect->getGlobalBounds().left - 10, tempRect->getGlobalBounds().top + 
		tempRect->getGlobalBounds().height + 6}, tempRect->getGlobalBounds().width + 20, {200, 200, 200, 255});
	sf::Text* startGameTxt = m_ui.addText("Start Game", "title", { m_screenCenter.x, m_screenCenter.y - 60 }, true, 40);
	sf::Text* quitGameTxt =  m_ui.addText("Quit", "title", {m_screenCenter.x, m_screenCenter.y + 60}, true, 40);

	eMainMenu menuOption{ eMainMenu::eNone };
	sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition());
	while (m_window->isOpen() && m_gameState == eGameState::eMenu) {
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed
			else if (event.type == sf::Event::MouseMoved) {
				if (startGameTxt->getGlobalBounds().contains({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) })) {
					menuOption = eMainMenu::eStart;
					//startGameTxt->setFillColor({ 100, 100, 100, 255 });
					startGameTxt->setStyle(sf::Text::Bold);
					startGameTxt->setPosition({ m_screenCenter.x - startGameTxt->getGlobalBounds().width / 2, m_screenCenter.y - 40 });
				}
				else {
					menuOption = eMainMenu::eNone;
					//startGameTxt->setFillColor({ 255, 255, 255, 255 });
					startGameTxt->setStyle(sf::Text::Regular);
					startGameTxt->setPosition({ m_screenCenter.x - startGameTxt->getGlobalBounds().width / 2, m_screenCenter.y - 40 });
				}
			}
		}

		m_window->clear({ 0, 0, 0, 255 });   // Remove previous frame
		m_ui.draw(m_window);  // Draw UI
		m_window->display();  // Show new frame
	}
}

void Game::startGame() {
	m_ui.clearAll();  // Reset UI elements

	m_ui.addText("Score", "basic", { m_screenSizef.x - 125, 0}, true, 30, sf::Text::Underlined);
	m_ui.addLineY({ m_screenSizef.x - 250, 0 }, m_screenSize.y);
	m_ui.addRectTexture("snake.png", { m_screenSizef.x - 210, 60 }, { 30, 30 }, 180);

	sf::Clock secondClock;
	float waterLevel{ 100.0f };
	while (m_window->isOpen() && m_gameState == eGameState::eGame && m_snakes.size() > 0) {
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Up:  // Manaual water control
					waterLevel += 0.5f;
					m_tank->setWaterLevel(waterLevel);
					break;
				case sf::Keyboard::Down:
					waterLevel -= 0.5f;
					m_tank->setWaterLevel(waterLevel);
					break;
				}
			}
		}

		//if (secondClock.getElapsedTime() >= sf::milliseconds(100)) {
		//	waterLevel -= 0.5f;
		//	if (waterLevel < 10.0f)
		//		waterLevel = 100.0f;
		//	//std::cout << waterLevel << '\n';
		//	m_tank->setWaterLevel(waterLevel);
		//	secondClock.restart();
		//}

		if (m_ticks.getElapsedTime() >= sf::seconds(1.0f / m_tps)) {  // Keep update rate independent to FPS
			m_ticks.restart();
			if (m_fruits.size() < 5 && rand() % 80 == 0 || m_fruits.size() == 0)  // Ramdomly spawn fruit (min 1, max 5)
				addFruit();

			m_input.update();  // Check input keys

			for (int i{ 0 }; i < m_fruits.size(); i++) {  // Update fruit
				m_fruits[i]->update();
			}
			for (int i{ 0 }; i < m_snakes.size(); i++)  // Update snakes
				m_snakes[i]->update();

			m_collision.update();

			for (int i{ 0 }; i < m_snakes.size(); i++) {
				if (!m_snakes[i]->m_isAlive)
					delSnake(m_snakes[i]);
			}
			for (int i{ 0 }; i < m_fruits.size(); i++) {  // Check if any fruit have died
				if (!m_fruits[i]->m_isAlive)
					delFruit(m_fruits[i]);
			}

			m_ui.update();  // Update UI last
		}
		m_ani.update();  // Run animations independent of game ticks

		m_window->clear({ 0, 0, 0, 255 });   // Remove previous frame
		m_draw.update(m_window);  // Draw entities & objects
		m_tank->drawTank(m_window);  // Draw tank body
		m_tank->drawWater(m_window);  // Draw tank water
		m_ui.draw(m_window);  // Draw UI
		m_window->display();  // Show new frame
	}
}

void Game::addSnake() {
	sf::FloatRect tankRect = *m_tank->getRect();
	Snake* tempSnake = new Snake({ tankRect.left + tankRect.width / 2, tankRect.top + tankRect.height / 2 }, m_tank->getRect(), m_screenSize, false, true);
	m_input.addInterface(tempSnake);
	m_collision.addInterface(tempSnake);
	m_draw.addInterface(tempSnake);
	m_snakes.push_back(tempSnake);
}

void Game::delSnake(Snake* obj) {
	m_input.removeInterface(obj);
	m_collision.removeInterface(obj);
	m_draw.removeInterface(obj);
	m_snakes.erase(std::find(m_snakes.begin(), m_snakes.end(), obj));
	delete obj;
}

void Game::addFruit() {
	Fruit* tempFruit = new Fruit(weightedRand(Fruit::Probabilities) + 2, m_tank->getRect(), CollisionType::eCircle);
	m_collision.addInterface(tempFruit);
	m_draw.addInterface(tempFruit);
	m_ani.addInterface(tempFruit);
	m_fruits.push_back(tempFruit);
}

void Game::delFruit(Fruit* obj) {
	m_collision.removeInterface(obj);
	m_draw.removeInterface(obj);
	m_ani.removeInterface(obj);
	m_fruits.erase(std::find(m_fruits.begin(), m_fruits.end(), obj));
}

unsigned int Game::weightedRand(const std::vector<unsigned int> probabilities) {
	unsigned int totalProbability{ 0 };
	for (unsigned int probability : probabilities)
		totalProbability += probability;

	unsigned int randValue = rand() % totalProbability;
	for (int i{ 0 }; i < std::size(probabilities); i++) {
		if (randValue < probabilities[i])
			return i;
		randValue -= probabilities[i];
	}
	return 0;  // Failsafe, should never be called!
}
