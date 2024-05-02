#pragma once
#include <iostream>
#include "ICollision.h"
#include "IDraw.h"
#include "IAnimate.h"

class Fruit : public ICollision, public IDraw, public IAnimate {
public:
	static const std::vector<unsigned int> Probabilities;
	bool m_isAlive{ false };
	bool m_isRegistered{ false };
	Fruit();
	Fruit(unsigned int value, sf::FloatRect* tank, CollisionType collision = CollisionType::eRect);
	void init(unsigned int value, sf::FloatRect* tank, CollisionType collision = CollisionType::eRect);
	static void loadTextures();  // Load textures
	void setPos(const sf::Vector2f newPos);  // Move the fruit to a new position
	int getValue();  // Return m_value
	sf::FloatRect getRect() override;  // From ICollision.h
	float getRadius() override;  // From ICollision.h
	sf::Vector2f getCircleCenter() override;  // From ICollision.h
	bool isColliding(ICollision& other) override;  // From ICollision.h
	void collideSnake() override;  // From ICollision.h
	void collideFruit(const int value) override;  // From ICollision.h
	void update();
	void animate(sf::RenderWindow* window) override;  // From IAnimate.h
	void draw(sf::RenderWindow* window) override;  // From IDraw.h
private:
	static sf::Texture Texture[4];
	int m_value{ 0 };
	sf::Vector2f m_pos{ 0, 0 };
	sf::FloatRect* m_tank;
	sf::Sprite m_sprite;
	int m_aniOffset{ 0 };
	bool m_aniDir{ true };
};

