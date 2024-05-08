#include "Game.h"

const unsigned int Game::MaxSnakes = 2;  // Maximum amount of players
const unsigned int Game::MaxFruits = 5;  // Maximum amount of fruit
const sf::Color Game::Player1Col = { 0, 255, 0, 255 };  // Player 1 colour
const sf::Color Game::Player2Col = { 255, 255, 0, 255 };  // Player 2 colour

Game::Game() {
	srand(static_cast<unsigned int>(time(NULL)));
	sf::ContextSettings settings;  // Setup window settings
	settings.antialiasingLevel = 8;

	Snake::loadTextures();  // Load snake textures
	Fruit::loadTextures();  // Load fruit textures
	m_tank = new Tank({ 40, 40, static_cast<float>(m_screenSize.x - 330), static_cast<float>(m_screenSize.y - 60) });  // Create tank class
	for (int i{ 0 }; i < MaxSnakes; i++) {
		m_snakes[i] = new Snake();
	}
	for (int i{ 0 }; i < MaxFruits; i++) {
		m_fruits[i] = new Fruit();
	}

	m_window = new sf::RenderWindow(sf::VideoMode(m_screenSize.x, m_screenSize.y), "Water Snakes - D3169324", sf::Style::Default, settings);  // Create window
	m_window->setFramerateLimit(m_fps);  // Set target framerate
}

void Game::begin() {
	std::cout << m_input.setP1Controller(0) << '\n';  // Controller debugging
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
		tempRect->getGlobalBounds().height + 6}, static_cast<unsigned int>(tempRect->getGlobalBounds().width + 20), {200, 200, 200, 255});
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
		m_draw.update(m_window);  // Draw entities & objects
		m_ui.draw(m_window);  // Draw UI
		m_window->display();  // Show new frame
	}
}

void Game::startGame() {
	m_ui.clearAll();  // Reset UI elements
	m_ui.addLineY({ m_screenSizef.x - 250, 0 }, m_screenSize.y);  // Draw border geometry

	for (int i{ 0 }; i < MaxSnakes; i++) {  // Make sure all entities are dead so we only revive the ones we need
		if (m_snakes[i]->m_isAlive)
			killSnake(m_snakes[i]);
	}
	for (int i{ 0 }; i < MaxFruits; i++) {
		if (m_fruits[i]->m_isAlive)
			killFruit(m_fruits[i]);
	}
	m_snakeAmount = 0;
	m_fruitAmount = 0;

	sf::FloatRect* rect = m_tank->getRect();
	resetSnake(0, { (rect->width / 2) + rect->left - (rect->width / 4), rect->height / 2 + rect->top });  // Spawn 2 snakes
	resetSnake(1, { (rect->width / 2) + rect->left + (rect->width / 4), rect->height / 2 + rect->top });

	std::vector<sf::Text*> scores;  // Create a vector of scores (text)
	std::vector<sf::Text*> breaths;  // 
	float tempStartY = 70;  // Starting Y position of scores
	float tempBreathY = (m_screenSizef.y / 2) + 70;
	float tempSpacing = 50;  // Spacing between scores
	float tempIconX = m_screenSizef.x - 210;  // X position of snake icon
	float tempTextX = m_screenSizef.x - 180;  // X position of snake score & breath

	m_ui.addText("Score", "basic", { m_screenSizef.x - 125, 0 }, true, 30, sf::Text::Underlined);
	m_ui.addText("Breath", "basic", { m_screenSizef.x - 125, tempBreathY - 70 }, true, 30, sf::Text::Underlined);

	for (int i{ 0 }; i < MaxSnakes; i++) {
		m_ui.addRectTexture("snake", { tempIconX, static_cast<float>(tempStartY + (tempSpacing * i)) }, {30, 30}, 180, (i == 0) ? Player1Col : Player2Col);  // Load texture icon for snake
		scores.push_back(m_ui.addText(std::to_string(m_snakes[i]->getScore()) , "basic", { tempTextX, static_cast<float>(tempStartY + (tempSpacing * i)) - 17 }, false));  // Text is not centred so -(size/2) to make it line up
		
		m_ui.addRectTexture("snake", { tempIconX, static_cast<float>(tempBreathY + (tempSpacing * i)) }, { 30, 30 }, 180, (i == 0) ? Player1Col : Player2Col);  // Load texture icon for snake
		breaths.push_back(m_ui.addText(std::to_string(m_snakes[i]->getBreathRemaining()), "basic", { tempTextX, static_cast<float>(tempBreathY + (tempSpacing * i)) - 17 }, false));
	}

	sf::Clock waterClock;  // Create clock to track water
	sf::Clock secondClock;
	float waterLevel{ 100.0f };
	m_tank->setWaterLevel(waterLevel);  // Make sure to reset tank (from last game cycle)
	while (m_window->isOpen() && m_gameState == eGameState::eGame && m_snakeAmount > 1) {
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

		if (waterClock.getElapsedTime() >= sf::seconds(1)) {
			waterLevel -= (100 / 90);
			m_tank->setWaterLevel(waterLevel);
			waterClock.restart();
		}

		if (m_ticks.getElapsedTime() >= sf::seconds(1.0f / m_tps)) {  // Keep update rate independent to FPS
			m_ticks.restart();
			if ((m_fruitAmount < 5 && rand() % 80 == 0) || m_fruitAmount < 1) {  // Ramdomly spawn fruit (min 1, max 5)
				for (int i{ 0 }; i < MaxFruits; i++) {  // Reset the first fruit that is dead
					if (!m_fruits[i]->m_isAlive) {
						resetFruit(i);
						break;
					}
				}
			}

			m_input.update();  // Check input keys

			for (int i{ 0 }; i < MaxFruits; i++) {  // Update fruit
				if (m_fruits[i]->m_isAlive)
					m_fruits[i]->update();
				if (!m_fruits[i]->m_isAlive && m_fruits[i]->m_isRegistered)  // Not alive but registered
					killFruit(m_fruits[i]);
			}

			for (int i{ 0 }; i < MaxSnakes; i++) {  // Update snakes
				if (m_snakes[i]->m_isAlive)
					m_snakes[i]->update();
				if (!m_snakes[i]->m_isAlive && m_snakes[i]->m_isRegistered)  // Not alive but registered
					killSnake(m_snakes[i]);
			}

			m_collision.update();  // Run collision between entities

			for (int i{ 0 }; i < MaxSnakes; i++) {  // Check if any snakes have died & update scores
				if (m_snakes[i]->m_isAlive && std::to_string(m_snakes[i]->getScore()) != scores[i]->getString())  // If alive & score has changed
					scores[i]->setString(std::to_string(m_snakes[i]->getScore()));  // Update UI text
				else if (!m_snakes[i]->m_isAlive)
					scores[i]->setFillColor({ 255, 80, 80, 255 });

				if (m_snakes[i]->m_isAlive && std::to_string(m_snakes[i]->getBreathRemaining()) != breaths[i]->getString()) {  // If alive & score has changed
					breaths[i]->setString(std::to_string(m_snakes[i]->getBreathRemaining()));
					breaths[i]->setFillColor({ 255, 255, 255, 255 });
				}
				if (breaths[i]->getString() == '0') {  // Flash red when 0
					if (static_cast<unsigned int>(secondClock.getElapsedTime().asSeconds()) % 2 == 0)
						breaths[i]->setFillColor({ 255, 80, 80, 255 });
					else
						breaths[i]->setFillColor({ 255, 255, 255, 255 });
				}
			}

			m_ui.update();  // Update UI last
		}

		m_window->clear({ 0, 0, 0, 255 });   // Remove previous frame
		m_draw.update(m_window);  // Draw entities & objects
		m_tank->drawTank(m_window);  // Draw tank body
		m_tank->drawWater(m_window);  // Draw tank water
		m_ani.update(m_window);  // Draw animations & SFX
		m_ui.draw(m_window);  // Draw UI
		m_window->display();  // Show new frame
	}

	m_ui.clearAll();
	m_ui.addText("Scores", "basic", { m_screenCenter.x, 10 }, true, 40, sf::Text::Underlined);
	scores.clear();
	breaths.clear();
	float tempScoreY = 110;
	tempSpacing = 70;  // Spacing between scores
	tempIconX = m_screenCenter.x - 10;  // X position of snake icon
	tempTextX = m_screenCenter.x;  // X position of snake score
	for (int i{ 0 }; i < MaxSnakes; i++) {
		scores.push_back(m_ui.addText(std::to_string(m_snakes[i]->getScore()), "basic", { tempTextX, static_cast<float>(tempScoreY + (tempSpacing * i)) - 17 }, true));
		m_ui.addRectTexture("snake", { tempIconX - scores[i]->getGlobalBounds().width / 2 - 20, static_cast<float>(tempScoreY + (tempSpacing * i))}, {30, 30}, 180, (i == 0) ? Player1Col : Player2Col);  // Load texture icon for snake
	}

	std::string tempStr;
	if (m_snakes[0]->getScore() > m_snakes[1]->getScore())
		tempStr = "Player 1 Wins!";
	else if (m_snakes[0]->getScore() < m_snakes[1]->getScore())
		tempStr = "Player 2 Wins!";
	else
		tempStr = "It's a Tie!";
	m_ui.addText(tempStr, "basic", { m_screenCenter.x, m_screenCenter.y + 100 }, true, 50);

	bool mouseClick{ false };  // If mouse button is clicked
	while (m_window->isOpen() && m_gameState == eGameState::eGame) {
		sf::Event event;  // Fetch & process window events
		while (m_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				m_window->close();  // Quit if window closed or Esc pressed
			else if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
				case sf::Keyboard::Return:
				case sf::Keyboard::Space:
					m_gameState = eGameState::eMenu;
				}
			}
		}

		mouseClick = sf::Mouse::isButtonPressed(sf::Mouse::Left);  // Update mouse button
		if (mouseClick)
			m_gameState = eGameState::eMenu;

		m_window->clear({ 0, 0, 0, 255 });
		m_ui.draw(m_window);
		m_window->display();  // Show frame
	}

	for (int i{ 0 }; i < MaxFruits; i++) {  // Kill all fruit
		if (m_fruits[i]->m_isRegistered)
			killFruit(m_fruits[i]);
	}
	for (int i{ 0 }; i < MaxSnakes; i++) {  // Kill all fruit
		if (m_snakes[i]->m_isRegistered)
			killSnake(m_snakes[i]);
	}

	m_gameState = eGameState::eMenu;  // Return to menu once game is finished
	return;  // Return to Game::begin(), which will run menu
}

void Game::resetSnake(const unsigned int index, const sf::Vector2f pos) {
	m_snakes[index]->init(static_cast<unsigned int>(m_snakeAmount + 1), (index == 0) ? Player1Col : Player2Col, pos, m_tank->getRect(), m_screenSize, true, true, 5);
	m_input.addInterface(m_snakes[index]);
	m_collision.addInterface(m_snakes[index]);
	m_draw.addInterface(m_snakes[index]);
	m_ani.addInterface(m_snakes[index]);
	m_snakeAmount++;
	m_snakes[index]->m_isRegistered = true;
}

void Game::killSnake(Snake* obj) {
	m_input.removeInterface(obj);
	m_collision.removeInterface(obj);
	m_draw.removeInterface(obj);
	m_ani.removeInterface(obj);
	m_snakeAmount--;
	obj->m_isRegistered = false;
	obj->m_isAlive = false;
}

void Game::resetFruit(const unsigned int index) {
	m_fruits[index]->init(weightedRand(Fruit::Probabilities) + 2, m_tank->getRect(), CollisionType::eCircle);
	m_collision.addInterface(m_fruits[index]);
	m_draw.addInterface(m_fruits[index]);
	m_ani.addInterface(m_fruits[index]);
	m_fruitAmount++;
	std::cout << "Reset fruit\n";
	m_fruits[index]->m_isRegistered = true;
}

void Game::killFruit(Fruit* obj) {
	m_collision.removeInterface(obj);
	m_draw.removeInterface(obj);
	m_ani.removeInterface(obj);
	m_fruitAmount--;
	std::cout << "Kill fruit\n";
	obj->m_isRegistered = false;
	obj->m_isAlive = false;
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
