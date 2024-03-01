#include "game.h"

void game::begin() {
	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Snake");
	m_window->setFramerateLimit(m_fps);  // Set target framerate

	m_circle.setFillColor({ 255, 255, 255, 255 });
	m_circle.setRadius(10);
	m_circle.setOrigin({ m_circle.getRadius(), m_circle.getRadius() });

	sf::Texture texture1;
	if (!texture1.loadFromFile("Apple.png")) {
		std::cerr << "Failed to load Apple.png" << '\n';
	}
	sf::Texture texture2;
	if (!texture2.loadFromFile("GoldApple.png")) {
		std::cerr << "Failed to load GoldApple.png" << '\n';
	}

	m_circle.setTexture(&texture1);

	sf::Sprite apple1;
	apple1.setTexture(texture1);

	sf::Sprite apple2;
	apple2.setTexture(texture2);
	apple2.setPosition({ 0, 32 });

	inputManager input = inputManager();
	snake* player1 = new snake({ static_cast<float>(m_screenSize.x / 2), static_cast<float>(m_screenSize.y / 2) }, 20);
	input.registerObserver(player1);


	bool skipFrame{ false };
	while (m_window->isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed
		}

		input.update();  // Check input keys
		player1->update();

		m_window->clear({ 255, 255, 255, 255 });   // Remove previous frame
		m_window->draw(apple1);
		m_window->draw(apple2);
		player1->draw(m_window);
		m_window->display();
	}
}
