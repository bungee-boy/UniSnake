#include "game.h"

void game::begin() {
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Snake", sf::Style::Default, settings);
	m_window->setFramerateLimit(m_fps);  // Set target framerate

	sf::Texture texture1;
	if (!texture1.loadFromFile("Apple.png")) {
		std::cerr << "Failed to load Apple.png" << '\n';
	}
	sf::Texture texture2;
	if (!texture2.loadFromFile("GoldApple.png")) {
		std::cerr << "Failed to load GoldApple.png" << '\n';
	}

	drawManager draw = drawManager();
	inputManager input = inputManager();
	collisionManager collision = collisionManager();

	snake* player1 = new snake({ static_cast<float>(m_screenSize.x / 2), static_cast<float>(m_screenSize.y / 2) }, 100);
	input.addInterface(player1);
	collision.addInterface(player1);
	draw.addInterface(player1);

	fruit* apple1 = new fruit(5, texture1, { 150.0f, 150.0f }, collisionType::eCircle);
	collision.addInterface(apple1);
	draw.addInterface(apple1);

	while (m_window->isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed
		}

		input.update();  // Check input keys

		player1->update();

		collision.update();

		m_window->clear({ 100, 100, 100, 255 });   // Remove previous frame
		draw.update(m_window);
		m_window->display();
	}
}
