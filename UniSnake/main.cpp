#include "main.h"

using namespace std;

// https://www.youtube.com/watch?v=7j5yW5QDC2U
// Water takes 90 seconds to empty
// Maximum of 5 food on the screen at once


int main() {
	gWindow.setFramerateLimit(gFps);  // Set target framerate

	sf::Vector2i playerPos{ gWidth / 2, gHeight / 2};
	sf::Vector2f playerVel{ 0, 0 };

	while (gWindow.isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (gWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gWindow.close();  // Quit if window closed or Esc pressed
		}

		gWindow.clear();   // Remove previous frame

		gWindow.display();
	}
}