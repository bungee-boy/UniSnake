#pragma once
#include <vector>
#include <iostream>
#include "ICollision.h"
#include "Snake.h"
#include "Fruit.h"

class CollisionManager {
public:
	void addInterface(ICollision* interface);
	void removeInterface(ICollision* interface);
	void checkCollision(ICollision* current, ICollision* other);
	void update();
private:
	std::vector<ICollision*> m_interfaces;
};
