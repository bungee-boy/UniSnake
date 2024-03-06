#pragma once
#include <iostream>
#include "iCollision.h"
#include "iDraw.h"

class fruit : public iCollision, public iDraw {
public:
	bool m_isAlive{ true };
	sf::Sprite m_sprite;
	sf::Vector2f m_pos{ 0, 0 };
	fruit(int value, sf::Texture* texture, sf::Vector2f pos, collisionType collision = collisionType::eRect);
	void move(float x = 0, float y = 0);
	int getValue();
	sf::FloatRect getRect();  // From iCollision.h
	float getRadius();  // From iCollision.h
	sf::Vector2f getCircleCenter();  // From iCollision.h
	bool isColliding(iCollision* other) override;  // From iCollision.h
	void collideSnake();  // From iCollision.h
	void collideFruit(int value);  // From iCollision.h
	void draw(sf::RenderWindow* window) override;  // From iDraw.h
private:
	int m_value{ 0 };
	sf::Texture m_texture;
};

