#include "Snake.h"

const float Snake::Pi = 3.14159265359f;
const float Snake::Size = 10.0f;
const float Snake::NodeGap = 1.1f;
const float Snake::TurnSpeed = 3;
const float Snake::TurnMax = 15;
const float Snake::TurnSmoothing = 4;
const unsigned int Snake::Gravity = 10;

sf::Texture Snake::Body::Texture = sf::Texture();

Snake::Body::Body(sf::Vector2f pos, float direction, Snake* parent) {
	setCollisionType(CollisionType::eCircle);
	m_parent = parent;
	m_shape.setRadius(Size);
	m_shape.setOrigin(Size, Size);
	m_shape.setRotation(direction - 180);
	m_shape.setTexture(&Texture);
	m_pos = pos;
	m_shape.setPosition(m_pos);
}

sf::Vector2f Snake::Body::getCircleCenter() {
	return m_pos;
}

sf::FloatRect Snake::Body::getRect() {
	return m_shape.getGlobalBounds();
}

float Snake::Body::getRadius() {
	return Size;
}

bool Snake::Body::isColliding(ICollision& other) {
	switch (other.getCollisionType()) {
	case CollisionType::eRect:
		break;
	case CollisionType::eCircle: {
		sf::Vector2f offset = getCircleCenter() - other.getCircleCenter();
		float distance = (offset.x * offset.x) + (offset.y * offset.y);  // Offset ^ 2

		float radius = getRadius() + other.getRadius();
		radius *= radius;  // Radius ^ 2

		if (distance <= radius)
			return true;
	}
	}
	return false;
}

void Snake::Body::collideSnake() {
	std::cout << "Snake::Body -> collideSnake()\n";
}

void Snake::Body::collideFruit(int value) {
	std::cout << "Snake::Body -> collideFruit(" << value << ")\n";
}

void Snake::Body::draw(sf::RenderWindow* window) {
	window->draw(m_shape);
}

Snake::Snake(const sf::Vector2f startPos, sf::FloatRect* waterRect, const sf::Vector2u screenSize, const bool collideWithSelf, const bool bounceOffWalls, const int length) {  // Constructor
	setCollisionType(CollisionType::eCircle);
	m_screenSize = screenSize;  // Set screen size
	m_waterRect = waterRect;  // Set screen bounds
	m_collideSelf = collideWithSelf;  // Set collide with self
	m_bounceWall = bounceOffWalls;  // Set bounce off walls
	if (!Body::Texture.loadFromFile("textures\\snake.png"))  // Load texture
		std::cerr << "Failed to load snake.png" << '\n';
	Body::Texture.setSmooth(true);
	m_pos = startPos;
	m_addNodes = length;
	for (int i{ 0 }; i < length; i++) {  // Fill linked list
		m_body.push_back(Body(m_pos, m_dir, this));
		m_pos.y += Size + NodeGap;
	}
	m_pos = startPos;
}

void Snake::handleInput(InputActions action, float dataValue) {
	if (m_waterRect->contains(m_pos)) {  // Limit to only in water
		switch (action) {
		case InputActions::eP1Left:  // Turn left
			if (dataValue == 0.0f) {  // Keyboard
				if (m_dirVel > 0)  // Ignore 
					m_dirVel = 0;
				if (m_dirVel > -TurnMax)
					m_dirVel -= TurnSpeed;
			}
			else {  // Controller
				m_dirVel = (TurnMax / 100) * dataValue;
			}
			break;
		case InputActions::eP1Right:  // Turn right
			if (dataValue == 0.0f) {  // Keyboard
				if (m_dirVel < 0)
					m_dirVel = 0;
				if (m_dirVel < TurnMax)
					m_dirVel += TurnSpeed;
			}
			else {  // Controller
				m_dirVel = (TurnMax / 100) * dataValue;
			}
			break;
		default:  // No input
			if (m_dirVel >= TurnSmoothing && m_dirVel > 0)
				m_dirVel -= TurnSmoothing;
			else if (m_dirVel <= TurnSmoothing && m_dirVel < 0)
				m_dirVel += TurnSmoothing;
			else if (m_dirVel != 0)
				m_dirVel = 0;
			break;
		}

		if (m_dirVel != 0) {
			m_dir += m_dirVel;  // Add velocity to direction

			if (m_dir >= 360)  // Limit the rotation between 0 - 359
				m_dir -= 360;
			else if (m_dir < 0)
				m_dir += 360;
		}
	}
}

sf::Vector2f Snake::getCircleCenter() { 
	if (m_body.getHead() == nullptr)
		throw "Head is nullptr, cannot return center!";
	return m_body.getHead()->data.getCircleCenter();
}

sf::FloatRect Snake::getRect() {
	if (m_body.getHead() == nullptr)
		throw "Head is nullptr, cannot return rect!";
	return m_body.getHead()->data.getRect();
}

float Snake::getRadius() {
	return Size;
}

bool Snake::isColliding(ICollision& other) {
	ListNode<Body>* currNode = m_body.getHead();
	while (currNode != nullptr) {  // Check each node in linked list
		if (currNode->data.isColliding(other))
			return true;
		currNode = currNode->next;
	}
	
	return false;
}

void Snake::collideSnake() {
	std::cout << "Snake -> collideSnake()\n";
}

void Snake::collideFruit(int value) {
	m_addNodes += value;
}

void Snake::update() {
	if (m_body.getTail()->data.getCircleCenter().x < 0 || m_body.getTail()->data.getCircleCenter().x > m_screenSize.x ||
		m_body.getTail()->data.getCircleCenter().y > m_screenSize.y) {  // If tail has gone off screen
		m_isAlive = false;  // Mark self for deletion
		return;  // Stop all updates
	}
		
	if (m_collideSelf) {  // Check collision with self
		ListNode<Body>* currNode = m_body.getHead()->next;  // start at head + 1
		if (currNode != nullptr)
			currNode = currNode->next;
		while (currNode != nullptr) {  // Check each node in linked list
			if (currNode->data.isColliding(m_body.getHead()->data)) {
				m_isAlive = false;
				break;
			}
			currNode = currNode->next;
		}
	}

	if (m_addNodes > 0) {  // Allow snake to grow
		if (m_body.getHead() != nullptr) {  // Can only grow if there is an existing node
			m_body.push_back(Body(m_body.getHead()->data.m_pos, m_body.getHead()->data.m_shape.getRotation(), this));
			m_addNodes--;
		}
		else
			m_addNodes = 0;
	}

	m_pos.x += std::roundf(cos((-m_dir + 90) * (Pi / 180)) * Size * NodeGap);  // Move the head by the velocity
	m_pos.y -= std::roundf(sin((-m_dir + 90) * (Pi / 180)) * Size * NodeGap);

	// Screen bounds collision
	if (m_pos.x < m_waterRect->left + Size) {  // Left
		if (m_bounceWall) {
			m_pos.x = m_waterRect->left + Size;  // Snap back to inside the wall
			m_dir = 90 - (m_dir - 270);  // Angle to bounce off wall
		}
		else
			gravity();
	}
	else if (m_pos.x > m_waterRect->left + m_waterRect->width - Size) {  // Right
		if (m_bounceWall) {
			m_pos.x = m_waterRect->left + m_waterRect->width - Size;  // Snap back to inside the wall
			m_dir = 90 - (m_dir - 270);  // Angle to bounce off wall
		}
		else
			gravity();
	}

	if (m_pos.y < m_waterRect->top + Size) {  // Top
		gravity();
	}
	else if (m_pos.y > m_waterRect->top + m_waterRect->height - Size) {  // Bottom
		if (m_bounceWall) {
			m_pos.y = m_waterRect->top + m_waterRect->height - Size;  // Snap back to inside the wall
			m_dir = 180 - m_dir;  // Angle to bounce off wall
		}
		else
			gravity();
	}

	m_body.push_front(Body(m_pos, m_dir, this));  // Add new node to head
	m_body.pop_back();  // Remove tail node
}

void Snake::draw(sf::RenderWindow* window) {
	ListNode<Body>* currNode = m_body.getTail();  // Start at tail
	while (currNode != nullptr) {  // Draw each node in linked list (in reverse so head on top)
		currNode->data.draw(window);
		currNode = currNode->prev;
	}
}

void Snake::gravity() {
	if (m_dir > 180.0f)  // Facing left
		m_dir -= Gravity;  // Turn down
	else if (m_dir < 180.0f) // Facing right
		m_dir += Gravity;  // Turn down
	else if (m_dir != 180.0f && m_dir != -180.0f)  // Facing down
		m_dir = (rand() % 2) ? 180.0f : -180.0f;
}
