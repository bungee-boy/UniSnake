#include "snake.h"

snake::snake(const sf::Vector2f startPos, const int length) {
	if (!texture1.loadFromFile("SnakeSegment.png")) {
		std::cerr << "Failed to load SnakeSegment.png" << '\n';
	}
	texture1.setSmooth(true);
	m_pos = startPos;
	for (int i{ 0 }; i < length; i++) {
		addNode(m_pos, 0, &texture1);
	}
	m_pos.x = startPos.x;
}

void snake::handleInput(inputActions action) {
	if (m_updateCount == m_speed) {
		if (action == inputActions::eP1Left)
			m_direction -= 10;
		else if (action == inputActions::eP1Right)
			m_direction += 10;
	}
}

void snake::update() {
	if (m_updateCount == m_speed) {
		if (m_direction >= 360)  // Limit the rotation between 0 - 359
			m_direction -= 360;
		else if (m_direction < 0)
			m_direction += 360;

		m_vel.x = std::round(cos(-m_direction * (PI / 180)) * m_size * 1.5);  // Calculate the head's velocity
		m_vel.y = -std::round(sin(-m_direction * (PI / 180)) * m_size * 1.5);

		std::cout << m_direction << '\n' << m_vel.x << ' ' << m_vel.y << '\n';

		if (m_pos.x <= 0 && m_vel.x < 0) {  // Wall collision
			m_vel.x = -m_vel.x;
			m_direction += 90;
		}

		m_pos.x += m_vel.x;  // Move head by the velocity
		m_pos.y += m_vel.y;

		addNode(m_pos, m_direction - 90, &texture1, false);  // Add new node to head
		delNode();  // Remove tail node

		m_updateCount = 0;
	}
	else
		m_updateCount++;
}

void snake::draw(sf::RenderWindow* window) {
	m_node* currNode = m_head;
	while (currNode != nullptr) {  // Draw every node in linked list
		window->draw(currNode->shape);
		currNode = currNode->next;
	}
}

void snake::addNode(const sf::Vector2f pos, const float direction, const sf::Texture *texture, const bool to_tail) {  // Initialise a node
	m_node* newNode = new m_node;  // Create new node
	newNode->shape.setRadius(m_size);
	newNode->shape.setOrigin(m_size, m_size);
	newNode->shape.setRotation(direction);
	newNode->shape.setTexture(texture);
	newNode->pos = pos;
	newNode->shape.setPosition(newNode->pos);

	if (m_head == nullptr)  // If list is empty
		m_head = newNode;  // Set to head
	else {
		if (to_tail) {  // Add to tail
			if (m_tail == nullptr) {  // If tail is none
				m_head->next = newNode;  // Point head to tail
				m_tail = newNode;  // Set tail
			}
			else {  // Tail exists
				m_tail->next = newNode;  // Point tail to new
				m_tail = newNode;  // Set tail to new
			}
		}
		else {  // Add to head
			newNode->next = m_head;  // Point new to head
			m_head = newNode;  // Set head to new
		}
	}
}

void snake::delNode(const bool del_tail) {
	if (del_tail) {  // Delete tail
		m_node* currNode = m_head;  // Get tail - 1 and set to tail
		while (currNode->next != m_tail)
			currNode = currNode->next;
		delete m_tail;  // Delete tail and replace with tail - 1
		m_tail = currNode;
		m_tail->next = nullptr;  // Remove pointer to old tail
	}
	else {  // Delete head
		m_node* oldHead = m_head;  // Save old head
		m_head = m_head->next;  // Move head down 1
		delete oldHead;  // Delete old head
	}
}
