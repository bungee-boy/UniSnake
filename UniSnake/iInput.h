#pragma once

enum class inputActions {
	eNone,
	eP1Left,
	eP1Right,
	eP2Left,
	eP2Right
};

class IInput {
public:
	virtual void handleInput(inputActions action) = 0;
};

