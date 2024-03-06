#pragma once

#include <iostream>
#include "iInput.h"
#include "iCollision.h"
#include "iDraw.h"

class snake : public iInput, public iCollision, public iDraw {
public:
	bool m_isAlive{ true };
	snake(const sf::Vector2f startPos, const int length = 1);
	void handleInput(inputActions action) override;  // From iInput.h
	sf::Vector2f getCircleCenter();  // From iCollision.h
	sf::FloatRect getRect();  // From iCollision.h
	float getRadius();  // From iCollision.h
	bool isColliding(iCollision* other) override;  // From iCollision.h
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
	static const int Speed;  // Movement speed of the snake (update rate)
	sf::Vector2f m_pos{ 0, 0 };  // Position
	sf::Vector2f m_vel{ 0, 0 };  // Velocity
	float m_dir{ 0 };  // Direction (rotation)
	float m_dirVel{ 0 };  // Direction velocity (rotation velocity)
	int m_updateCount{ 0 };  // Counter for update
	unsigned int m_addNodes{ 0 };  // Buffer of nodes to add

	class m_node : public iCollision {  // Node for linked list
	public:
		m_node(sf::Vector2f pos, float direction, snake* parent);
		sf::Vector2f getCircleCenter();  // From iCollision.h
		sf::FloatRect getRect();  // From iCollision.h
		float getRadius();  // From iCollision.h
		bool isColliding(iCollision* other) override;  // From iCollision.h
		void collideSnake();  // From iCollision.h
		void collideFruit(int value);  // From iCollision.h
		void draw(sf::RenderWindow* window);
	protected:
		friend class snake;  // Allow snake to access protected members
		static sf::Texture m_texture;  // Texture of all nodes
		static m_node* m_head;  // Head of linked list
		static m_node* m_tail;  // Tail of linked list
		m_node* m_next{ nullptr };  // Next node in linked list
		snake* m_parent{ nullptr };  // Ptr to parent snake (for collision)
	private:
		sf::Vector2f m_pos{ 0, 0 };  // Node position
		sf::CircleShape m_shape;  // Drawable surface
	};

	void addNode(const sf::Vector2f pos, const float direction, const bool to_tail = true);  // Add a new node to linked list
	void delNode(const bool del_tail = true);  // Delete the tail node
};

