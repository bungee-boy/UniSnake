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
	Snake(const unsigned int playerNum, const sf::Vector2f startPos, sf::FloatRect* waterRect, const sf::Vector2u screenSize, const bool collideWithSelf, const bool bounceOffWalls, const int length = 2);
	int getScore();
	void handleInput(InputActions action, float dataValue = 0) override;  // From IInput.h
	sf::Vector2f getCircleCenter() override;  // From ICollision.h
	sf::FloatRect getRect() override;  // From ICollision.h
	float getRadius() override;  // From ICollision.h
	bool isColliding(ICollision& other) override;  // From ICollision.h
	void collideSnake() override;  // From ICollision.h
	void collideFruit(int value) override;  // From ICollision.h
	void update();
	void draw(sf::RenderWindow* window) override;  // From IDraw.h
	void animate() override;  // From IAnimate.h
private:
	static const float Pi;  // Used for rotation
	static const float Size;  // Radius of snake's nodes
	static const float NodeGap;  // Separation between nodes (affects speed!)
	static const float TurnSpeed;  // Turning speed
	static const float TurnMax;  // Maximum turning amount
	static const float TurnSmoothing;  // Turning speed back to 0 (not pressing)
	static const unsigned int Gravity;  // Turning speed out of water
	static const unsigned int BubbleSpeed;  // Bubble animation speed (ms)
	static sf::Texture BubbleTexture[10];  // Array of textures (for bubble animation)
	InputActions m_leftKeyBind{ InputActions::eNone };  // Left keybind
	InputActions m_rightKeyBind{ InputActions::eNone };  // Right keybind
	sf::Vector2u m_screenSize;  // Screen size
	sf::FloatRect* m_waterRect;  // Screen boundary (tank)
	sf::Vector2f m_pos{ 0, 0 };  // Position
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

