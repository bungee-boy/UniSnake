#include "snake.h"

void snake::update() {
	if (updateCount == speed) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  // Player input
			direction -= 5;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			direction += 5;
		if (direction >= 360)  // Limit the rotation between 0 - 359
			direction -= 360;
		else if (direction < 0)
			direction += 360;

		vel.x += std::round(cos(-direction * (PI / 180)) * gCircle.getRadius() / 2);  // Move the snake's head (in the current direction)
		vel.y -= std::round(sin(-direction * (PI / 180)) * gCircle.getRadius() / 2);

		float offset = (direction - direction2);

		vel2.x = vel.x + std::round(cos(-(direction - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);  // Move the snake's head (in the current direction)
		vel2.y = vel.y - std::round(sin(-(direction - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);

		offset += (direction2 - direction3) * 2;

		vel3.x = vel2.x + std::round(cos(-(direction2 - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);  // Move the snake's head (in the current direction)
		vel3.y = vel2.y - std::round(sin(-(direction2 - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);

		offset += (direction3 - direction4) * 3;

		vel4.x = vel3.x + std::round(cos(-(direction3 - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);  // Move the snake's head (in the current direction)
		vel4.y = vel3.y - std::round(sin(-(direction3 - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);

		offset += (direction4 - direction5) * 4;

		vel5.x = vel4.x + std::round(cos(-(direction4 - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);  // Move the snake's head (in the current direction)
		vel5.y = vel4.y - std::round(sin(-(direction4 - offset - 180) * (PI / 180)) * gCircle.getRadius() * 2);

		updateCount = 0;

		direction5 = direction4;
		direction4 = direction3;
		direction3 = direction2;
		direction2 = direction;
	}
	else
		updateCount++;
}

void snake::draw(sf::RenderWindow& window) {
	gCircle.setFillColor({ 255, 255, 0, 255 });  // Draw snake
	gCircle.setPosition(vel5);
	window.draw(gCircle);
	gCircle.setFillColor({ 255, 0, 255, 255 });  // Draw snake
	gCircle.setPosition(vel4);
	window.draw(gCircle);
	gCircle.setFillColor({ 0, 0, 255, 255 });  // Draw snake
	gCircle.setPosition(vel3);
	window.draw(gCircle);
	gCircle.setFillColor({ 0, 255, 0, 255 });  // Draw snake
	gCircle.setPosition(vel2);
	window.draw(gCircle);
	gCircle.setFillColor({ 255, 0, 0, 255 });
	gCircle.setPosition(vel);
	window.draw(gCircle);
}
