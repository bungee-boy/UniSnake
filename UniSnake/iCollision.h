#pragma once
#include "SFML\Graphics.hpp"

enum class CollisionType {
	eRect,
	eCircle
};

class ICollision {
public:
	CollisionType getCollisionType() { return m_collisionType; };
	void setCollisionType(CollisionType type) { m_collisionType = type; };
	virtual sf::Vector2f getCircleCenter() = 0;
	virtual sf::FloatRect getRect() = 0;
	virtual float getRadius() = 0;
	virtual bool isColliding(ICollision& other) = 0;
	virtual void collideSnake() = 0;
	virtual void collideFruit(int value) = 0;
private:
	CollisionType m_collisionType{ CollisionType::eRect };  // Rect = use size, Circle = use radius
};
