#include "main.h"

using namespace std;

int main() {
	gWindow.setFramerateLimit(gFps);  // Set target framerate

	gCircle.setFillColor({ 255, 255, 255, 255 });
	gCircle.setRadius(10);
	gCircle.setOrigin({ gCircle.getRadius(), gCircle.getRadius() });

	sf::Texture texture1;
	if (!texture1.loadFromFile("Apple.png")) {
		std::cerr << "Failed to load Apple.png" << '\n';
	}
	sf::Texture texture2;
	if (!texture2.loadFromFile("GoldApple.png")) {
		std::cerr << "Failed to load GoldApple.png" << '\n';
	}

	gCircle.setTexture(&texture1);

	sf::Sprite apple1;
	apple1.setTexture(texture1);

	sf::Sprite apple2;
	apple2.setTexture(texture2);
	apple2.setPosition({ 0, 32 });

	snake player1 = snake(20);

	bool skipFrame{ false };
	while (gWindow.isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (gWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gWindow.close();  // Quit if window closed or Esc pressed
		}

		player1.update();

		gWindow.clear({255, 255, 255, 255});   // Remove previous frame
		gWindow.draw(apple1);
		gWindow.draw(apple2);
		player1.draw(gWindow);
		gWindow.display();
	}
}