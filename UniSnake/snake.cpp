#include "snake.h"

const float Snake::Pi = 3.14159265359f;
const float Snake::Size = 10.0f;
const float Snake::NodeGap = 1.3f;
const float Snake::TurnSpeed = 4;
const float Snake::TurnMax = 15;
const float Snake::TurnSmoothing = 2;
const unsigned int Snake::Speed = 3;

Snake::ListNode* Snake::ListNode::Head = nullptr;  // Head of linked list
Snake::ListNode* Snake::ListNode::Tail = nullptr;  // Tail of linked list
sf::Texture Snake::ListNode::Texture = sf::Texture();

Snake::ListNode::ListNode(sf::Vector2f pos, float direction, Snake* parent) {
	setCollisionType(CollisionType::eCircle);
	m_parent = parent;
	m_shape.setRadius(Size);
	m_shape.setOrigin(Size, Size);
	m_shape.setRotation(direction - 180);
	m_shape.setTexture(&Texture);
	m_pos = pos;
	m_shape.setPosition(m_pos);
}

sf::Vector2f Snake::ListNode::getCircleCenter() {
	return m_pos;
}

sf::FloatRect Snake::ListNode::getRect() {
	return m_shape.getGlobalBounds();
}

float Snake::ListNode::getRadius() {
	return Size;
}

bool Snake::ListNode::isColliding(ICollision* other) {
	switch (other->getCollisionType()) {
	case CollisionType::eRect:
		break;
	case CollisionType::eCircle: {
		sf::Vector2f offset = getCircleCenter() - other->getCircleCenter();
		float distance = (offset.x * offset.x) + (offset.y * offset.y);  // Offset ^ 2

		float radius = getRadius() + other->getRadius();
		radius *= radius;  // Radius ^ 2

		if (distance <= radius)
			return true;
	}
	}
	return false;
}

void Snake::ListNode::collideSnake() {
	std::cout << "Node -> collidedSnake()\n";
}

void Snake::ListNode::collideFruit(int value) {
	std::cout << "Node -> collidedFruit(" << value << ")\n";
}

void Snake::ListNode::draw(sf::RenderWindow* window) {
	window->draw(m_shape);
}

Snake::Snake(const sf::Vector2f startPos, const int length) {  // Constructor
	setCollisionType(CollisionType::eCircle);
	if (!ListNode::Texture.loadFromFile("SnakeSegment.png"))  // Load texture
		std::cerr << "Failed to load SnakeSegment.png" << '\n';
	ListNode::Texture.setSmooth(true);
	m_pos = startPos;
	for (int i{ 0 }; i < length; i++) {  // Init linked list
		addNode(m_pos, m_dir);
		m_pos.y += Size + NodeGap;
	}
	m_pos = startPos;
}

void Snake::handleInput(inputActions action) {
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
	return ListNode::Head->getCircleCenter();
}

sf::FloatRect Snake::getRect() {
	return ListNode::Head->getRect();
}

float Snake::getRadius() {
	return Size;
}

bool Snake::isColliding(ICollision* other) {
	if (other != nullptr) {
		ListNode* currNode = ListNode::Head;
		while (currNode != nullptr) {  // Check each node in linked list
			if (currNode->isColliding(other))
				return true;
			currNode = currNode->m_next;
		}
	}
	
	return false;
}

void Snake::collideSnake() {
	std::cout << "Snake -> collidedSnake()\n";
}

void Snake::collideFruit(int value) {
	m_addNodes += value;
}

void Snake::update() {
	if (m_updateCount == Speed) {
		ListNode* currNode = ListNode::Head->m_next;  // Check collision with self (start at head + 1)
		if (currNode != nullptr)
			currNode = currNode->m_next;
		while (currNode != nullptr) {  // Check each node in linked list
			if (currNode->isColliding(ListNode::Head)) {
				m_isAlive = false;
				break;
			}
			currNode = currNode->m_next;
		}

		if (m_addNodes > 0) {  // Allow snake to grow
			if (ListNode::Head != nullptr) {  // Can only grow if there is an existing node
				addNode(ListNode::Head->m_pos, ListNode::Head->m_shape.getRotation());
				m_addNodes--;
			}
			else
				m_addNodes = 0;
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

		addNode(m_pos, m_dir, false);  // Add new node to head
		delNode();  // Remove tail node

		m_updateCount = 0;
	}
	else
		m_updateCount++;
}

void Snake::draw(sf::RenderWindow* window) {
	ListNode* currNode = ListNode::Tail;
	while (currNode != nullptr) {  // Draw each node in linked list (in reverse so head on top)
		currNode->draw(window);
		currNode = currNode->m_prev;
	}
}

void Snake::addNode(const sf::Vector2f pos, const float direction, const bool to_tail) {  // Initialise a node
	ListNode* newNode = new ListNode(pos, direction, this);  // Create new node

	if (ListNode::Head == nullptr)  // If list is empty
		ListNode::Head = newNode;  // Set to head
	else {
		if (to_tail) {  // Add to tail
			if (ListNode::Tail == nullptr) {  // If tail is none
				ListNode::Head->m_next = newNode;  // Point head to tail (H -> T)
				newNode->m_prev = ListNode::Head;  // Point tail to head (H <- T)
				ListNode::Tail = newNode;  // Set tail
			}
			else {  // Tail exists
				ListNode::Tail->m_next = newNode;  // Point tail to new (T -> N)
				newNode->m_prev = ListNode::Tail;  // Point new to tail (T <- N)
				ListNode::Tail = newNode;  // Set tail to new
			}
		}
		else {  // Add to head
			newNode->m_next = ListNode::Head;  // Point new to head (N -> H)
			ListNode::Head->m_prev = newNode;  // Point head to new (N <- H)
			ListNode::Head = newNode;  // Set head to new
		}
	}
}

void Snake::delNode(const bool del_tail) {
	if (del_tail) {  // Delete tail
		ListNode* tempNode = ListNode::Tail->m_prev;  // Get tail - 1 (N -> N -> T)
		delete ListNode::Tail;  // Delete tail (N -> N -> D)
		ListNode::Tail = tempNode;  // Set tail to - 1 (N -> T ->  )
		ListNode::Tail->m_next = nullptr;  // Remove pointer to old tail (N -> T)
	}
	else {  // Delete head
		ListNode* oldHead = ListNode::Head;  // Save old head (H -> N -> N)
		ListNode::Head = ListNode::Head->m_next;  // Move head down 1 (D -> H -> N)
		delete oldHead;  // Delete old head (     H -> N)
	}
}
