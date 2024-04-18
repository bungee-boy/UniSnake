#include "Game.h"

Game::Game() {
	srand(static_cast<unsigned int>(time(NULL)));
	sf::ContextSettings settings;  // Setup window settings
	settings.antialiasingLevel = 8;

	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Snake - D3169324", sf::Style::Default, settings);  // Create window
	m_window->setFramerateLimit(m_fps);  // Set target framerate

	m_tank = new Tank({ 40, 40, static_cast<float>(m_screenSize.x - 330), static_cast<float>(m_screenSize.y - 60) });

	Fruit::loadTextures();  // Load fruit textures
}

void Game::begin() {
	std::cout << m_input.setP1Controller(0) << '\n';
	while (m_window->isOpen()) {  // Main loop
		addSnake();
		startGame();
	}
}

void Game::startGame() {
	sf::Clock secondClock;
	float waterLevel{ 100.0f };

	m_ui.addText("Score", "basic", { static_cast<float>(m_screenSize.x) - 125, 0}, true, 30, sf::Text::Underlined);
	m_ui.addLineY({ static_cast<float>(m_screenSize.x) - 250, 0 }, m_screenSize.y);
	m_ui.addRectTexture("snake.png", { static_cast<float>(m_screenSize.x) - 210, 60 }, { 30, 30 }, 180);
	
	while (m_window->isOpen() && m_snakes.size() > 0) {
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
		m_ani.update();
		m_window->clear({ 0, 0, 0, 255 });   // Remove previous frame
		m_draw.update(m_window);  // Draw new frame
		m_tank->drawTank(m_window);
		m_tank->drawWater(m_window);
		m_ui.draw(m_window);
		m_window->display();
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
