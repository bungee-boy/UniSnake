#pragma once
#include <iostream>
#include "IInput.h"
#include "ICollision.h"
#include "IDraw.h"

class Snake : public IInput, public ICollision, public IDraw {
public:
	bool m_isAlive{ true };
	Snake(const sf::Vector2f startPos, const sf::FloatRect screenBounds, const sf::Vector2u screenSize, const bool collideWithSelf, const bool bounceOffWalls, const int length = 2);
	void handleInput(InputActions action) override;  // From iInput.h
	sf::Vector2f getCircleCenter();  // From iCollision.h
	sf::FloatRect getRect();  // From iCollision.h
	float getRadius();  // From iCollision.h
	bool isColliding(ICollision* other) override;  // From iCollision.h
	void collideSnake();  // From iCollision.h
	void collideFruit(int value);  // From iCollision.h
	void update();
	void draw(sf::RenderWindow* window) override;  // From iDraw.h
private:
	static const float Pi;  // Used for rotation
	static const float Size;  // Radius of snake's nodes
	static const float NodeGap;  // Separation between nodes (affects speed!)
	static const float TurnSpeed;  // Turning speed
	static const float TurnMax;  // Maximum turning amount
	static const float TurnSmoothing;  // Turning speed back to 0 (not pressing)
	static const unsigned int Gravity;  // Turning speed out of water
	static const unsigned int Speed;  // Movement speed of the snake (update rate)
	sf::Vector2u m_screenSize;  // Screen size
	sf::FloatRect m_screenBounds;  // Screen boundary (tank)
	sf::Vector2f m_pos{ 0, 0 };  // Position
	float m_dir{ 0 };  // Direction (rotation)
	float m_dirVel{ 0 };  // Direction velocity (rotation velocity)
	unsigned int m_updateCount{ 0 };  // Counter for update
	unsigned int m_addNodes{ 0 };  // Buffer of nodes to add
	bool m_collideSelf{ true };  // Toggle colliding with itself
	bool m_bounceWall{ false };  // Toggle bouncing off walls

	class ListNode : public ICollision {  // Node for linked list
	public:
		ListNode(sf::Vector2f pos, float direction, Snake* parent);
		sf::Vector2f getCircleCenter() override;  // From iCollision.h
		sf::FloatRect getRect() override;  // From iCollision.h
		float getRadius() override;  // From iCollision.h
		bool isColliding(ICollision* other) override;  // From iCollision.h
		void collideSnake() override;  // From iCollision.h
		void collideFruit(int value) override;  // From iCollision.h
		void draw(sf::RenderWindow* window);
	protected:
		friend class Snake;  // Allow snake to access protected members
		static sf::Texture Texture;  // Texture of all nodes
		static ListNode* Head;  // Head of linked list
		static ListNode* Tail;  // Tail of linked list
		ListNode* m_prev{ nullptr };  // Previous node in linked list
		ListNode* m_next{ nullptr };  // Next node in linked list
		Snake* m_parent{ nullptr };  // Ptr to parent snake (for collision)
	private:
		sf::Vector2f m_pos{ 0, 0 };  // Node position
		sf::CircleShape m_shape;  // Drawable surface
	};

	void addNode(const sf::Vector2f pos, const float direction, const bool to_tail = true);  // Add a new node to linked list
	void delNode(const bool del_tail = true);  // Delete the tail node
	void gravity();  // Apply gravity
};

