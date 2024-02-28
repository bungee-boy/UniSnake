#include "snake.h"

snake::snake(const int length) {
	for (int i{ 0 }; i < length; i++) {
		addNode(m_pos, (colourToggle ? Col1 : Col2));
		m_pos.x -= m_size * 2;
		colourToggle = !colourToggle;
	}
	m_pos.x = gWidth / 2;
}

void snake::update() {
	if (m_updateCount == m_speed) {
		std::cout << m_direction << '\n';
		if (m_pos.x <= 0 && m_direction > 90) {
			if (m_direction > 180)
				m_direction += 90;
			else
				m_direction -= 90;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  // Player input
			m_direction -= 10;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			m_direction += 10;

		if (m_direction >= 360)  // Limit the rotation between 0 - 359
			m_direction -= 360;
		else if (m_direction < 0)
			m_direction += 360;

		m_pos.x += std::round(cos(-m_direction * (PI / 180)) * gCircle.getRadius() * 1.5);  // Move the snake's head (in the current direction)
		m_pos.y -= std::round(sin(-m_direction * (PI / 180)) * gCircle.getRadius() * 1.5);

		addNode(m_pos, (colourToggle ? Col1 : Col2), false);  // Add new node to head
		colourToggle = !colourToggle;
		delNode();  // Remove tail node

		m_updateCount = 0;
	}
	else
		m_updateCount++;
}

void snake::draw(sf::RenderWindow& window) {
	gCircle.setFillColor({ 255, 0, 0, 255 });
	gCircle.setPosition(m_pos);
	window.draw(gCircle);

	m_node* currNode = m_head;
	while (currNode != nullptr) {  // Draw every node in linked list
		window.draw(currNode->shape);
		currNode = currNode->next;
	}
}

void snake::addNode(const sf::Vector2f pos, const sf::Color colour, const bool to_tail) {  // Initialise a node
	m_node* newNode = new m_node;  // Create new node
	newNode->shape.setRadius(m_size);
	newNode->shape.setOrigin(m_size, m_size);
	newNode->shape.setFillColor(colour);
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
