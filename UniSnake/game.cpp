#include "game.h"

Game::Game() {
	srand(static_cast<unsigned int>(time(NULL)));
	sf::ContextSettings settings;  // Setup window settings
	settings.antialiasingLevel = 8;

	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Snake", sf::Style::Default, settings);  // Create window
	m_window->setFramerateLimit(m_fps);  // Set target framerate

	m_foodTexture1 = new sf::Texture;  // Load textures
	m_foodTexture2 = new sf::Texture;
	if (!m_foodTexture1->loadFromFile("Apple.png"))
		std::cerr << "Failed to load Apple.png" << '\n';
	if (!m_foodTexture2->loadFromFile("GoldApple.png"))
		std::cerr << "Failed to load GoldApple.png" << '\n';
}

void Game::begin() {
	addSnake();
	addFruit();

	while (m_window->isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed
		}

		if (m_fruits.size() < 5 && rand() % 100 == 0) {
			addFruit();
		}

		m_input.update();  // Check input keys

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

		m_window->clear({ 100, 100, 100, 255 });   // Remove previous frame
		m_draw.update(m_window);
		m_window->display();
	}
}

void Game::addSnake() {
	Snake* tempSnake = new Snake({ static_cast<float>(m_screenSize.x / 2), static_cast<float>(m_screenSize.y / 2) }, 5);
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
}

void Game::addFruit() {
	Fruit* tempFruit = new Fruit(10, m_foodTexture1, { static_cast<float>(rand() % m_screenSize.x), static_cast<float>(rand() % m_screenSize.y) }, CollisionType::eCircle);
	m_collision.addInterface(tempFruit);
	m_draw.addInterface(tempFruit);
	m_fruits.push_back(tempFruit);
}

void Game::delFruit(Fruit* obj) {
	m_collision.removeInterface(obj);
	m_draw.removeInterface(obj);
	m_fruits.erase(std::find(m_fruits.begin(), m_fruits.end(), obj));
}
