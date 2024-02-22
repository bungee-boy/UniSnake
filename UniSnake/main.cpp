#include "main.h"

using namespace std;

// https://www.youtube.com/watch?v=7j5yW5QDC2U
// Water takes 90 seconds to empty
// Maximum of 5 food on the screen at once


int main() {
	//gWindow.setKeyRepeatEnabled(false);  // Disable windows keyboard delay (for holding keys)
	gWindow.setFramerateLimit(gFps);  // Set target framerate

	gCircle.setFillColor({ 255, 255, 255, 255 });
	gCircle.setRadius(5);
	gCircle.setOrigin({ gCircle.getRadius(), gCircle.getRadius() });
	
	sf::Vector2f playerPos{ gWidth / 2, gHeight / 2};
	sf::Vector2f playerPos2{ gWidth / 2, gHeight / 2 };
	sf::Vector2f playerPos3{ gWidth / 2, gHeight / 2 };
	sf::Vector2f playerVel{ 0, 0 };  // Temp velocity for skipped frame
	sf::Vector2f playerVel2{ 0, 0 };  // Actual velocity that updates snake
	int direction{ 0 };

	//float a = 0.0f;
	//float velocity = 0.0f;
	//float acceleration = 0.001f;
	//
	//a += velocity;
	//velocity += acceleration;

	bool skipFrame{ false };
	while (gWindow.isOpen()) {  // Main loop
		sf::Event event;  // Fetch & process window events
		while (gWindow.pollEvent(event)) {
			if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				gWindow.close();  // Quit if window closed or Esc pressed
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  // Player input
			direction -= 5;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction += 5;
		if (direction >= 360)  // Limit the rotation between 0 - 359
			direction -= 360;
		else if (direction < 0)
			direction += 360;
		std::cout << direction << '\n';

		playerVel.x = std::round(cos(-direction * (pi / 180)) * gCircle.getRadius() * 2);  // Do the math to rotate the vector
		playerVel.y = -std::round(sin(-direction * (pi / 180)) * gCircle.getRadius() * 2);

		if (!skipFrame) {  // Only update snake every other frame (too fast)
			playerPos.x += playerVel2.x;
			playerPos.y += playerVel2.y;
			playerVel2.x = 0;
			playerVel2.y = 0;
			skipFrame = true;
		}
		else {  // Hold the 'unseen' position for next frame
			playerVel2.x += playerVel.x;
			playerVel2.y += playerVel.y;
			skipFrame = false;
		}

		gWindow.clear();   // Remove previous frame
		gCircle.setFillColor({ 0, 0, 255, 255 });  // Draw snake
		gCircle.setPosition(playerPos3);
		gWindow.draw(gCircle);
		gCircle.setFillColor({ 0, 255, 0, 255 });  // Draw snake
		gCircle.setPosition(playerPos2);
		gWindow.draw(gCircle);
		gCircle.setFillColor({ 255, 0, 0, 255 });
		gCircle.setPosition(playerPos);
		gWindow.draw(gCircle);
		gWindow.display();

		if (!skipFrame) {  // Move the snake after drawn because next frame is unseen
			playerPos3 = playerPos2;
			playerPos2 = playerPos;
		}
	}
}