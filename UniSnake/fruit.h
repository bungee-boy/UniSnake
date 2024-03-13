#pragma once
#include <iostream>
#include "ICollision.h"
#include "IDraw.h"

class Fruit : public ICollision, public IDraw {
public:
	static const std::vector<unsigned int> Probabilities;
	bool m_isAlive{ true };
	Fruit(unsigned int value, sf::FloatRect screenBounds, CollisionType collision = CollisionType::eRect);
	static void loadTextures();  // Load textures
	void move(float x = 0, float y = 0);  // Shift the fruit by an amount
	int getValue();  // Return m_value
	sf::FloatRect getRect();  // From iCollision.h
	float getRadius();  // From iCollision.h
	sf::Vector2f getCircleCenter();  // From iCollision.h
	bool isColliding(ICollision* other) override;  // From iCollision.h
	void collideSnake();  // From iCollision.h
	void collideFruit(int value);  // From iCollision.h
	void draw(sf::RenderWindow* window) override;  // From iDraw.h
private:
	static sf::Texture TextureTwo;
	static sf::Texture TextureThree;
	static sf::Texture TextureFour;
	static sf::Texture TextureFive;
	int m_value{ 0 };
	sf::Vector2f m_pos{ 0, 0 };
	sf::Sprite m_sprite;
};

