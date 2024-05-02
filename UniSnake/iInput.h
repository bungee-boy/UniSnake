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
	bool m_isAlive{ true };
	virtual void handleInput(InputActions action, float dataValue = 0.0f) = 0;
};

