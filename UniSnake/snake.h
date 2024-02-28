#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>

extern const double PI;
extern sf::CircleShape gCircle;
extern const unsigned int gWidth, gHeight;
extern sf::Color Col1, Col2;

class snake {
public:
	snake(const int length = 1);
	void update();
	void draw(sf::RenderWindow& window);
private:
	const float m_size{ 10 };
	sf::Vector2f m_pos{ static_cast<float>(gWidth / 2), static_cast<float>(gHeight / 2) };  // Current position
	sf::Vector2f m_vel{ 0, 0 };  // Current velocity
	int m_direction{ 0 };  // Current direction
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

	void addNode(const sf::Vector2f pos, const int direction, const sf::Texture *texture, const bool to_tail = true);
	void delNode(const bool del_tail = true);  // Delete the tail node
};

