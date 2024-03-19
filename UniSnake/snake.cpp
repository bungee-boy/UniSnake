#include "Snake.h"

const float Snake::Pi = 3.14159265359f;
const float Snake::Size = 10.0f;
const float Snake::NodeGap = 1.1f;
const float Snake::TurnSpeed = 3;
const float Snake::TurnMax = 15;
const float Snake::TurnSmoothing = 4;
const unsigned int Snake::Gravity = 10;

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
	std::cout << "Node -> collideSnake()\n";
}

void Snake::ListNode::collideFruit(int value) {
	std::cout << "Node -> collideFruit(" << value << ")\n";
}

void Snake::ListNode::draw(sf::RenderWindow* window) {
	window->draw(m_shape);
}

Snake::Snake(const sf::Vector2f startPos, sf::FloatRect* waterRect, const sf::Vector2u screenSize, const bool collideWithSelf, const bool bounceOffWalls, const int length) {  // Constructor
	setCollisionType(CollisionType::eCircle);
	m_screenSize = screenSize;  // Set screen size
	m_waterRect = waterRect;  // Set screen bounds
	m_collideSelf = collideWithSelf;  // Set collide with self
	m_bounceWall = bounceOffWalls;  // Set bounce off walls
	if (!ListNode::Texture.loadFromFile("textures\\snake.png"))  // Load texture
		std::cerr << "Failed to load snake.png" << '\n';
	ListNode::Texture.setSmooth(true);
	m_pos = startPos;
	m_addNodes = length;
	for (int i{ 0 }; i < length; i++) {  // Init linked list
		addNode(m_pos, m_dir);
		m_pos.y += Size + NodeGap;
	}
	m_pos = startPos;
}

Snake::~Snake() {
	while (ListNode::Head != nullptr)  // Delete all nodes (memory leak if not)
		delNode();
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
	if (ListNode::Head == nullptr)
		throw "Head is nullptr, cannot return center!";
	return ListNode::Head->getCircleCenter();
}

sf::FloatRect Snake::getRect() {
	if (ListNode::Head == nullptr)
		throw "Head is nullptr, cannot return rect!";
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
	std::cout << "Snake -> collideSnake()\n";
}

void Snake::collideFruit(int value) {
	m_addNodes += value;
}

void Snake::update() {
	if (ListNode::Tail->getCircleCenter().x < 0 || ListNode::Tail->getCircleCenter().x > m_screenSize.x ||
		ListNode::Tail->getCircleCenter().y > m_screenSize.y) {  // If tail has gone off screen
		m_isAlive = false;  // Mark self for deletion
		return;  // Stop all updates
	}
		
	if (m_collideSelf) {  // Check collision with self
		ListNode* currNode = ListNode::Head->m_next;  // start at head + 1
		if (currNode != nullptr)
			currNode = currNode->m_next;
		while (currNode != nullptr) {  // Check each node in linked list
			if (currNode->isColliding(ListNode::Head)) {
				m_isAlive = false;
				break;
			}
			currNode = currNode->m_next;
		}
	}

	if (m_addNodes > 0) {  // Allow snake to grow
		if (ListNode::Head != nullptr) {  // Can only grow if there is an existing node
			addNode(ListNode::Head->m_pos, ListNode::Head->m_shape.getRotation());
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

	addNode(m_pos, m_dir, false);  // Add new node to head
	delNode();  // Remove tail node
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
	if (del_tail) {  // Remove from tail
		if (ListNode::Tail == nullptr && ListNode::Head != nullptr) {  // If only head
			delete ListNode::Head;  // Delete head
			ListNode::Head = nullptr;
		}
		else if (ListNode::Tail != nullptr) {  // If tail exists
			ListNode::Tail = ListNode::Tail->m_prev;  // Remove tail
			delete ListNode::Tail->m_next;
			ListNode::Tail->m_next = nullptr;
			if (ListNode::Tail == ListNode::Head)  // If head and tail are same
				ListNode::Tail = nullptr;  // Don't delete but set tail to null
		}
		else
			std::cerr << "WARN -> Snake::delNode(true) called when list is empty!\n";
	}
	else {  // Remove from head
		if (ListNode::Head == nullptr && ListNode::Tail != nullptr) {  // If only tail (should never happen!)
			delete ListNode::Tail;
			ListNode::Tail = nullptr;
			std::cerr << "WARN -> Snake::delNode(false) ListNode::Head was nullptr when ListNode::Tail was not!\n";
		}
		else if (ListNode::Head != nullptr) {  // If head exists
			ListNode::Head = ListNode::Head->m_next;
			delete ListNode::Head->m_prev;
			ListNode::Head->m_prev = nullptr;
			if (ListNode::Head == ListNode::Tail)  // If head and tail are same
				ListNode::Tail = nullptr;  // Don't delete but set tail to null
		}
		else
			std::cerr << "WARN -> Snake::delNode(false) called when list is empty!\n";
	}
}

void Snake::gravity() {
	if (m_dir > 180)  // Facing left
		m_dir -= Gravity;  // Turn down
	else if (m_dir < 180) // Facing right
		m_dir += Gravity;  // Turn down
	else if (m_dir != 180 && m_dir != -180)  // Facing down
		m_dir = (rand() % 2) ? 180 : -180;
}
