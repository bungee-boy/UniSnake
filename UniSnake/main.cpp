#include "main.h"

using namespace std;

int main() {
	gWindow.setFramerateLimit(gFps);  // Set target framerate

	gCircle.setFillColor({ 255, 255, 255, 255 });
	gCircle.setRadius(10);
	gCircle.setOrigin({ gCircle.getRadius(), gCircle.getRadius() });

	snake player1 = snake(5);

	bool skipFrame{ false };
	while (gWindow.isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (gWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gWindow.close();  // Quit if window closed or Esc pressed
		}

		player1.update();

		gWindow.clear();   // Remove previous frame
		player1.draw(gWindow);
		gWindow.display();
	}
}