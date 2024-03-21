#pragma once
#include <vector>
#include <iostream>
#include "IAnimate.h"

class AnimateManager {
public:
	void addInterface(IAnimate* interface);
	void removeInterface(IAnimate* interface);
	void update();
private:
	std::vector<IAnimate*> m_interfaces;
};
