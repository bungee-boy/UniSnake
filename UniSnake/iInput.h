#pragma once

enum class InputActions {
	eNone,
	eP1Left,
	eP1Right,
	eP2Left,
	eP2Right
};

class IInput {
public:
	virtual void handleInput(InputActions action) = 0;
};

