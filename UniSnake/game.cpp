#include "Game.h"

Game::Game() {
	srand(static_cast<unsigned int>(time(NULL)));
	sf::ContextSettings settings;  // Setup window settings
	settings.antialiasingLevel = 8;

	Fruit::loadTextures();  // Load fruit textures
	m_tank = new Tank({ 40, 40, static_cast<float>(m_screenSize.x - 330), static_cast<float>(m_screenSize.y - 60) });  // Create tank class

	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Water Snakes - D3169324", sf::Style::Default, settings);  // Create window
	m_window->setFramerateLimit(m_fps);  // Set target framerate
}

void Game::begin() {
	//std::cout << m_input.setP1Controller(0) << '\n';  // Controller debugging
	while (m_window->isOpen()) {  // Main loop
		switch (m_gameState) {
		case eGameState::eMenu:
			startMenu();
			break;
		case eGameState::eGame:
			startGame();
			break;
		}
	}
}

void Game::startMenu() {
	m_ui.clearAll();  // Reset UI text & geometry
	sf::Text* tempRect = m_ui.addText("Water Snakes", "title", { m_screenCenter.x, 40 }, true, 50, sf::Text::Underlined);  // Setup UI text & geometry
	m_ui.addLineX({ tempRect->getGlobalBounds().left - 10, tempRect->getGlobalBounds().top + 
		tempRect->getGlobalBounds().height + 6}, tempRect->getGlobalBounds().width + 20, {200, 200, 200, 255});
	sf::Text* startGameTxt = m_ui.addText("Start Game", "title", { m_screenCenter.x, m_screenCenter.y - 60 }, true, 40);
	sf::Text* quitGameTxt =  m_ui.addText("Quit", "title", {m_screenCenter.x, m_screenCenter.y + 60}, true, 40);

	eMainMenu menuOption{ eMainMenu::eNone };  // Which menu option is selected
	bool mouseClick{ false };  // If mouse button is clicked
	while (m_window->isOpen() && m_gameState == eGameState::eMenu) {
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed

			else if (event.type == sf::Event::MouseMoved) {  // Mouse has moved
				if (startGameTxt->getGlobalBounds().contains({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) })) {  // Mouse is over txt
					menuOption = eMainMenu::eStart;  // Set current menu option
					startGameTxt->setStyle(sf::Text::Bold);
					startGameTxt->setPosition({ m_screenCenter.x - startGameTxt->getGlobalBounds().width / 2, m_screenCenter.y - 60 });
				}
				else if (menuOption == eMainMenu::eStart) {  // Undo menu option when mouse not over txt
					menuOption = eMainMenu::eNone;
					startGameTxt->setStyle(sf::Text::Regular);
					startGameTxt->setPosition({ m_screenCenter.x - startGameTxt->getGlobalBounds().width / 2, m_screenCenter.y - 60 });
				}

				if (quitGameTxt->getGlobalBounds().contains({ static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y) })) {  // Mouse is over txt
					menuOption = eMainMenu::eQuit;  // Set current menu option
					quitGameTxt->setStyle(sf::Text::Bold);
					quitGameTxt->setPosition({ m_screenCenter.x - quitGameTxt->getGlobalBounds().width / 2, m_screenCenter.y + 60 });
				}
				else if (menuOption == eMainMenu::eQuit) {  // Undo menu option when mouse not over txt
					menuOption = eMainMenu::eNone;
					quitGameTxt->setStyle(sf::Text::Regular);
					quitGameTxt->setPosition({ m_screenCenter.x - quitGameTxt->getGlobalBounds().width / 2, m_screenCenter.y + 60 });
				}
			}
		}

		mouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);  // Update mouse button
		switch (menuOption) {
		case eMainMenu::eStart:  // START
			if (mouseClick) { // Toggle colour based on if menu option is clicked or not
				startGameTxt->setFillColor({ 200, 200, 200, 255 });
				m_window->clear({ 0, 0, 0, 255 });   // Refresh frame to show new text colour
				m_ui.draw(m_window);  // Draw UI
				m_window->display();  // Show new frame
				sf::sleep(sf::milliseconds(50));  // Delay to show user changed colour
				m_gameState = eGameState::eGame;  // START GAME
				return;  // Exit loop to Game::begin(), which will start the game
			}
			else
				startGameTxt->setFillColor({ 255, 255, 255, 255 });
			break;

		case eMainMenu::eQuit:  // QUIT
			if (mouseClick) { // Toggle colour based on if menu option is clicked or not
				quitGameTxt->setFillColor({ 200, 200, 200, 255 });
				m_window->clear({ 0, 0, 0, 255 });   // Refresh frame to show new text colour
				m_ui.draw(m_window);  // Draw UI
				m_window->display();  // Show new frame
				sf::sleep(sf::milliseconds(50));  // Delay to show user changed colour
				m_window->close();
			}
			else
				quitGameTxt->setFillColor({ 255, 255, 255, 255 });
			break;

		case eMainMenu::eNone:  // Do nothing if no menu option
		default:
			break;
		}

		m_window->clear({ 0, 0, 0, 255 });   // Remove previous frame
		m_ui.draw(m_window);  // Draw UI
		m_window->display();  // Show new frame
	}
}

void Game::startGame() {
	m_ui.clearAll();  // Reset UI elements
	m_ui.addText("Score", "basic", { m_screenSizef.x - 125, 0}, true, 30, sf::Text::Underlined);  // Setup UI text & geometry
	m_ui.addLineY({ m_screenSizef.x - 250, 0 }, m_screenSize.y);

	addSnake({ 100, 100 });  // Spawn snakes *TEMPORARY*
	addSnake({ 150, 150 });

	std::vector<sf::Text*> scores;  // Create a vector of scores (text)
	float tempStartY = 70;  // Starting Y position of scores
	float tempSpacing = 50;  // Spacing between scores
	float tempIconX = m_screenSizef.x - 210;  // X position of snake icon
	float tempTextX = m_screenSizef.x - 180;  // X position of snake score
	for (int i{ 0 }; i < m_snakes.size(); i++) {
		m_ui.addRectTexture("snake", { tempIconX, static_cast<float>(tempStartY + (tempSpacing * i)) }, {30, 30}, 180);  // Load texture icon for snake
		scores.push_back(m_ui.addText(std::to_string(m_snakes[i]->getScore()) , "basic", { tempTextX, static_cast<float>(tempStartY + (tempSpacing * i)) - 15 }, false));  // Text is not centred so -(size/2) to make it line up
	}

	sf::Clock secondClock;  // Create clock to track seconds
	float waterLevel{ 100.0f };
	m_tank->setWaterLevel(waterLevel);  // Make sure to reset tank (from last game cycle)
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

			m_collision.update();  // Run collision between entities

			for (int i{ 0 }; i < m_snakes.size(); i++) {  // Check if any snakes have died & update scores
				if (std::to_string(m_snakes[i]->getScore()) != scores[i]->getString())  // If score has changed
					scores[i]->setString(std::to_string(m_snakes[i]->getScore()));  // Update UI text

				if (!m_snakes[i]->m_isAlive)  // If snake is dead
					delSnake(m_snakes[i]);  // Remove snake
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

	m_gameState = eGameState::eMenu;  // Return to menu once game is finished
	return;  // Return to Game::begin(), which will run menu
}

void Game::addSnake(const sf::Vector2f pos) {
	sf::FloatRect tankRect = *m_tank->getRect();
	Snake* tempSnake = new Snake(pos, m_tank->getRect(), m_screenSize, false, true);
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
