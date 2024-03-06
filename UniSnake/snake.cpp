#include "snake.h"

const float snake::Pi = 3.14159265359f;
const float snake::Size = 10.0f;
const float snake::NodeGap = 1.3f;
const float snake::TurnSpeed = 4;
const float snake::TurnMax = 15;
const float snake::TurnSmoothing = 2;
const int snake::Speed = 3;

snake::m_node* snake::m_node::m_head = nullptr;  // Head of linked list
snake::m_node* snake::m_node::m_tail = nullptr;  // Tail of linked list
sf::Texture snake::m_node::m_texture = sf::Texture();

snake::m_node::m_node(sf::Vector2f pos, float direction, snake* parent) {
	setCollisionType(collisionType::eCircle);
	m_parent = parent;
	m_shape.setRadius(Size);
	m_shape.setOrigin(Size, Size);
	m_shape.setRotation(direction - 180);
	m_shape.setTexture(&m_texture);
	m_pos = pos;
	m_shape.setPosition(m_pos);
}

sf::Vector2f snake::m_node::getCircleCenter() {
	return m_pos;
}

sf::FloatRect snake::m_node::getRect() {
	return m_shape.getGlobalBounds();
}

float snake::m_node::getRadius() {
	return Size;
}

bool snake::m_node::isColliding(iCollision* other) {
	switch (other->getCollisionType()) {
	case collisionType::eRect:
		break;
	case collisionType::eCircle: {
		sf::Vector2f offset = getCircleCenter() - other->getCircleCenter();
		float distance = (offset.x * offset.x) + (offset.y * offset.y);  // Offset ^ 2

		float radius = getRadius() + other->getRadius();
		radius *= radius;  // Radius ^ 2

		//std::cout << getCircleCenter().x << ',' << getCircleCenter().y << ' ' << other->getCircleCenter().x << ',' << other->getCircleCenter().y << '\n';
		if (distance <= radius)
			return true;
	}
	}
	return false;
}

void snake::m_node::collideSnake() {
	std::cout << "Node -> collidedSnake()\n";
}

void snake::m_node::collideFruit(int value) {
	std::cout << "Node -> collidedFruit(" << value << ")\n";
}

void snake::m_node::draw(sf::RenderWindow* window) {
	window->draw(m_shape);
}

snake::snake(const sf::Vector2f startPos, const int length) {  // Constructor
	setCollisionType(collisionType::eCircle);
	if (!m_node::m_texture.loadFromFile("SnakeSegment.png"))  // Load texture
		std::cerr << "Failed to load SnakeSegment.png" << '\n';
	m_node::m_texture.setSmooth(true);
	m_pos = startPos;
	for (int i{ 0 }; i < length; i++)  // Init linked list
		addNode(m_pos, m_dir);
}

void snake::handleInput(inputActions action) {
	if (m_updateCount == Speed) {
		switch (action) {
		case inputActions::eP1Left:  // Turn left
			if (m_dirVel > 0)  // Ignore 
				m_dirVel = 0;
			else if (m_dirVel > -TurnMax)
				m_dirVel -= TurnSpeed;
			break;
		case inputActions::eP1Right:  // Turn right
			if (m_dirVel < 0)
				m_dirVel = 0;
			else if (m_dirVel < TurnMax)
				m_dirVel += TurnSpeed;
			break;
		default:  // No input
			if (m_dirVel > 0)
				m_dirVel -= TurnSmoothing;
			else if (m_dirVel < 0)
				m_dirVel += TurnSmoothing;
			else if (m_dirVel == -TurnSpeed || m_dirVel == TurnSpeed)
				m_dirVel = 0;
		}

		//std::cout << m_dirVel << '\n';

		if (m_dirVel != 0) {
			m_dir += m_dirVel;

			if (m_dir >= 360)  // Limit the rotation between 0 - 359
				m_dir -= 360;
			else if (m_dir < 0)
				m_dir += 360;
		}
	}
}

sf::Vector2f snake::getCircleCenter() { 
	return m_node::m_tail->getCircleCenter();
}

sf::FloatRect snake::getRect() {
	return m_node::m_tail->getRect();
}

float snake::getRadius() {
	return Size;
}

bool snake::isColliding(iCollision* other) {
	if (other != nullptr) {
		m_node* currNode = m_node::m_head;
		while (currNode != nullptr) {  // Check each node in linked list
			if (currNode->isColliding(other))
				return true;
			currNode = currNode->m_next;
		}
	}
	
	return false;
}

void snake::collideSnake() {
	std::cout << "Snake -> collidedSnake()\n";
}

void snake::collideFruit(int value) {
	m_addNodes += value;
	//std::cout << "Snake -> collidedFruit(" << value << ")\n";
}

void snake::update() {
	if (m_updateCount == Speed) {
		m_node* currNode = m_node::m_head;  // Check collision with self
		while (currNode != nullptr || currNode == m_node::m_tail) {  // Check each node in linked list
			if (currNode->isColliding(m_node::m_tail)) {
				m_isAlive = false;
				break;
			}
			currNode = currNode->m_next;
		}

		if (m_addNodes > 0) {  // Allow snake to grow
			addNode(m_node::m_head->m_pos, m_node::m_head->m_shape.getRotation(), false);
			m_addNodes--;
		}

		m_vel.x = std::roundf(cos((- m_dir + 90) * (Pi / 180)) * Size * NodeGap);  // Calculate the head's velocity
		m_vel.y = -std::roundf(sin((-m_dir + 90) * (Pi / 180)) * Size * NodeGap);

		m_pos.x += m_vel.x;  // Move head by the velocity
		m_pos.y += m_vel.y;

		if (m_pos.x < Size) {  // Wall collision
			m_pos.x = Size;  // Snap back to inside the wall
			m_vel.x = -m_vel.x;  // Invert velocity
			m_dir = 90 - (m_dir - 270);  // Angle to bounce off wall
		}
		// The snake (visually) is reversed in relation to the linked list,
		//     so that the head is always drawn on top (last)
		addNode(m_pos, m_dir);  // Add new node to tail
		delNode(false);  // Remove head node

		m_updateCount = 0;
	}
	else
		m_updateCount++;
}

void snake::draw(sf::RenderWindow* window) {
	m_node* currNode = m_node::m_head;
	while (currNode != nullptr) {  // Draw each node in linked list
		currNode->draw(window);
		currNode = currNode->m_next;
	}
}

void snake::addNode(const sf::Vector2f pos, const float direction, const bool to_tail) {  // Initialise a node
	m_node* newNode = new m_node(pos, direction, this);  // Create new node

	if (m_node::m_head == nullptr)  // If list is empty
		m_node::m_head = newNode;  // Set to head
	else {
		if (to_tail) {  // Add to tail
			if (m_node::m_tail == nullptr) {  // If tail is none
				m_node::m_head->m_next = newNode;  // Point head to tail
				m_node::m_tail = newNode;  // Set tail
			}
			else {  // Tail exists
				m_node::m_tail->m_next = newNode;  // Point tail to new
				m_node::m_tail = newNode;  // Set tail to new
			}
		}
		else {  // Add to head
			newNode->m_next = m_node::m_head;  // Point new to head
			m_node::m_head = newNode;  // Set head to new
		}
	}
}

void snake::delNode(const bool del_tail) {
	if (del_tail) {  // Delete tail
		m_node* currNode = m_node::m_head;  // Get tail - 1 and set to tail
		while (currNode->m_next != m_node::m_tail)
			currNode = currNode->m_next;
		delete m_node::m_tail;  // Delete tail and replace with tail - 1
		m_node::m_tail = currNode;
		m_node::m_tail->m_next = nullptr;  // Remove pointer to old tail
	}
	else {  // Delete head
		m_node* oldHead = m_node::m_head;  // Save old head
		m_node::m_head = m_node::m_head->m_next;  // Move head down 1
		delete oldHead;  // Delete old head
	}
}
