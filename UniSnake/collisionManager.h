#pragma once
#include <vector>
#include <iostream>
#include "iCollision.h"
#include "snake.h"
#include "fruit.h"

class CollisionManager {
public:
	void addInterface(ICollision* interface);
	void removeInterface(ICollision* interface);
	void checkCollision(ICollision* current, ICollision* other);
	void update();
private:
	std::vector<ICollision*> m_interfaces;
};
