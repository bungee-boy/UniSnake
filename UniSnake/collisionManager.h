#pragma once
#include <vector>
#include <iostream>
#include "iCollision.h"
#include "snake.h"
#include "fruit.h"

class collisionManager {
public:
	void addInterface(iCollision* interface);
	void removeInterface(iCollision* interface);
	void checkCollision(iCollision* current, iCollision* other);
	void update();
private:
	std::vector<iCollision*> m_interfaces;
};
