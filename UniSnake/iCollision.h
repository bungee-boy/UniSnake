#pragma once
#include "SFML\Graphics.hpp"

enum class collisionType {
	eRect,
	eCircle
};

class iCollision {
public:
	collisionType getCollisionType() { return m_collisionType; };
	void setCollisionType(collisionType type) { m_collisionType = type; };
	virtual sf::Vector2f getCircleCenter() = 0;
	virtual sf::FloatRect getRect() = 0;
	virtual float getRadius() = 0;
	virtual bool isColliding(iCollision* other) = 0;
	virtual void collideSnake() = 0;
	virtual void collideFruit(int value) = 0;
private:
	collisionType m_collisionType{ collisionType::eRect };  // Rect = use size, Circle = use radius
};
