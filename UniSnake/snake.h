#pragma once
#include <iostream>
#include "LinkedList.h"
#include "IInput.h"
#include "ICollision.h"
#include "IDraw.h"
#include "IAnimate.h"

class Snake : public IInput, public ICollision, public IDraw, public IAnimate {
public:
	bool m_isAlive{ true };
	static void loadTextures();  // Load textures
	Snake();
	Snake(const unsigned int playerNum, const sf::Vector2f startPos, sf::FloatRect* waterRect, const sf::Vector2u screenSize, const bool collideWithSelf, const bool bounceOffWalls, const int length = 2);  // Constructor
	void init(const unsigned int playerNum, const sf::Vector2f startPos, sf::FloatRect* waterRect, const sf::Vector2u screenSize, const bool collideWithSelf, const bool bounceOffWalls, const int length = 2);  // Set default values
	int getScore();  // Return score
	void handleInput(InputActions action, float dataValue = 0) override;  // From IInput.h
	sf::Vector2f getCircleCenter() override;  // From ICollision.h
	sf::FloatRect getRect() override;  // From ICollision.h
	float getRadius() override;  // From ICollision.h
	bool isColliding(ICollision& other) override;  // From ICollision.h
	void collideSnake() override;  // From ICollision.h
	void collideFruit(int value) override;  // From ICollision.h
	void update();  // Update logic
	void draw(sf::RenderWindow* window) override;  // From IDraw.h
	void animate(sf::RenderWindow* window) override;  // From IAnimate.h
private:
	static const float Pi;
	static const float Size;
	static const float NodeGap;
	static const float TurnSpeed;
	static const float TurnMax;
	static const float TurnSmoothing;
	static const unsigned int Gravity;
	static const unsigned int BubbleSpeed;
	static const unsigned int BreathTime;
	static const unsigned int BreathDelay;
	static sf::Texture BubbleTexture[11];  // Array of textures (for bubble animation)
	static sf::RectangleShape BubbleFrames[11];  // Array of Rects (for bubble animation)
	InputActions m_leftKeyBind{ InputActions::eNone };  // Left keybind
	InputActions m_rightKeyBind{ InputActions::eNone };  // Right keybind
	sf::Vector2u m_screenSize;  // Screen size
	sf::FloatRect* m_waterRect;  // Screen boundary (tank)
	sf::Vector2f m_pos{ 0, 0 };  // Position
	sf::Vector2f m_bubblePos{ 0, 0 };  // Bubble animation position
	sf::Clock m_breathTimer;  // Bubble timer (decrease score / 1s when > BreathTime)
	int m_bubbleFrame{ 0 };  // Bubble animation frame
	bool m_showBubbles{ true };  // If bubbles are active
	float m_dir{ 0 };  // Direction (rotation)
	float m_dirVel{ 0 };  // Direction velocity (rotation velocity)
	unsigned int m_addNodes{ 0 };  // Buffer of nodes to add
	bool m_collideSelf{ true };  // Toggle colliding with itself
	bool m_bounceWall{ false };  // Toggle bouncing off walls

	class Body : public ICollision {  // Node for linked list
	public:
		Body(sf::Vector2f pos, float direction, Snake* parent);
		sf::Vector2f getCircleCenter() override;  // From iCollision.h
		sf::FloatRect getRect() override;  // From iCollision.h
		float getRadius() override;  // From iCollision.h
		bool isColliding(ICollision& other) override;  // From iCollision.h
		void collideSnake() override;  // From iCollision.h
		void collideFruit(int value) override;  // From iCollision.h
		void draw(sf::RenderWindow* window);
	protected:
		friend class Snake;  // Allow snake to access protected members
		static sf::Texture Texture;  // Texture of all nodes
		Snake* m_parent{ nullptr };  // Ptr to parent snake (for collision)
	private:
		sf::Vector2f m_pos{ 0, 0 };  // Node position
		sf::CircleShape m_shape;  // Drawable surface
	};
	LinkedList<Body> m_body;
	void gravity();  // Apply gravity
};

