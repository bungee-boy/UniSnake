#pragma once
#include <iostream>
#include "iCollision.h"
#include "iDraw.h"

class Fruit : public ICollision, public IDraw {
public:
	bool m_isAlive{ true };
	Fruit(int value, sf::Texture* texture, sf::Vector2f pos, CollisionType collision = CollisionType::eRect);
	void move(float x = 0, float y = 0);
	int getValue();
	sf::FloatRect getRect();  // From iCollision.h
	float getRadius();  // From iCollision.h
	sf::Vector2f getCircleCenter();  // From iCollision.h
	bool isColliding(ICollision* other) override;  // From iCollision.h
	void collideSnake();  // From iCollision.h
	void collideFruit(int value);  // From iCollision.h
	void draw(sf::RenderWindow* window) override;  // From iDraw.h
private:
	int m_value{ 0 };
	sf::Vector2f m_pos{ 0, 0 };
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

