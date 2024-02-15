#include "main.h"

using namespace std;


int main() {
	Map* map = new Map(gWindow.getSize());
	map->setCell({ 0, 0 }, true);
	gWindow.setFramerateLimit(gFps);  // Set target framerate

	while (gWindow.isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (gWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gWindow.close();  // Quit if window closed or Esc pressed
		}

		gWindow.clear();   // Remove previous frame
		map->draw(gWindow);
		gWindow.display();
	}
}