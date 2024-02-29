#pragma once

#include <iostream>
#include "SFML\Graphics.hpp"
#include "inputObserver.h"

const double PI = 3.14159265359;

class snake : public inputObserver{
public:
	snake(const sf::Vector2f startPos, const int length = 1);
	void handleInput(inputActions action) override;  // From input.h
	void update();
	void draw(sf::RenderWindow* window);
private:
	const float m_size{ 10 };
	sf::Vector2f m_pos{ 0, 0 };  // Current position
	sf::Vector2f m_vel{ 0, 0 };  // Current velocity
	float m_direction{ 0 };  // Current direction
	int m_speed{ 1 };  // Movement speed of the snake (update rate)
	int m_updateCount{ 0 };  // Counter to update

	sf::Texture texture1;
	struct m_node {  // Node for linked list
		m_node* next{ nullptr };
		sf::Vector2f pos{ 0, 0 };
		sf::CircleShape shape;
	};
	m_node* m_head{ nullptr };  // Head of linked list
	m_node* m_tail{ nullptr };  // Tail of linked list

	void addNode(const sf::Vector2f pos, const float direction, const sf::Texture *texture, const bool to_tail = true);
	void delNode(const bool del_tail = true);  // Delete the tail node
};

