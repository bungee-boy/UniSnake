#pragma once
#include <iostream>

template <typename T> struct ListNode {  // Linked list node
	ListNode* prev{ nullptr };  // Pointer to prev
	ListNode* next{ nullptr };  // Pointer to next
	T data;  // Data of the node
};

template <typename T> class LinkedList {
public:
	~LinkedList() {  // Default deconstructor
		clear();
	};
	int size() {  // Get size (length) of list
		return m_size;
	}
	ListNode<T>* getHead() {  // Get head ptr
		return m_head; 
	};
	ListNode<T>* getTail() {  // Get tail ptr
		return m_tail; 
	};
	void push_front(const T& data) {  // Add a new node to head
		ListNode<T>* newNode = new ListNode<T>{ nullptr, nullptr, data };  // Create new node

		if (m_head == nullptr)  // If list is empty
			m_head = newNode;  // Set to head
		else {  // Add to head
			newNode->next = m_head;  // Point new to head (N -> H)
			m_head->prev = newNode;  // Point head to new (N <- H)
			m_head = newNode;  // Set head to new
		}
		m_size++;  // Increase size
	};
	void pop_front() {  // Delete a node from head 
		if (m_head == nullptr && m_tail != nullptr) {  // If only tail (should never happen!)
			delete m_tail;  // Fix error
			m_tail = nullptr;
			m_size--;  // Decrease size
			std::cerr << "WARN -> LinkedList::pop_front() Head was nullptr while Tail was not!\n";
		}
		else if (m_head != nullptr) {  // If head exists
			m_head = m_head->next;
			delete m_head->prev;
			m_head->prev = nullptr;
			if (m_head == m_tail)  // If head and tail are same
				m_tail = nullptr;  // Don't delete but set tail to null
			m_size--;  // Decrease size
		}
		else
			std::cerr << "WARN -> LinkedList::pop_front() called when list is empty!\n";
	}
	void push_back(const T& data) {  // Add node to tail
		ListNode<T>* newNode = new ListNode<T>{ nullptr, nullptr, data };  // Create new node

		if (m_head == nullptr)  // If list is empty
			m_head = newNode;  // Set to head
		else {  // Add to tail
			if (m_tail == nullptr) {  // If tail is none
				m_head->next = newNode;  // Point head to tail (H -> T)
				newNode->prev = m_head;  // Point tail to head (H <- T)
				m_tail = newNode;  // Set tail
			}
			else {  // Tail exists
				m_tail->next = newNode;  // Point tail to new (T -> N)
				newNode->prev = m_tail;  // Point new to tail (T <- N)
				m_tail = newNode;  // Set tail to new
			}
		}
		m_size++;  // Increase size
	}
	void pop_back() {  // Delete from tail
		if (m_tail == nullptr && m_head != nullptr) {  // If only head
			delete m_head;  // Delete head
			m_head = nullptr;
			m_size--;  // Decrease size
		}
		else if (m_tail != nullptr) {  // If tail exists
			m_tail = m_tail->prev;  // Remove tail
			delete m_tail->next;
			m_tail->next = nullptr;
			if (m_tail == m_head)  // If head and tail are same
				m_tail = nullptr;  // Don't delete but set tail to null
			m_size--;  // Decrease size
		}
		else
			std::cerr << "WARN -> LinkedList::pop_back() called when list is empty!\n";
	}
	void clear() {  // Clear whole list
		while (m_head != nullptr)  // Cleanup all nodes from memory
			pop_back();
	}
private:
	int m_size{ 0 };  // Size of list
	ListNode<T>* m_head{ nullptr };  // Pointer to head
	ListNode<T>* m_tail{ nullptr };  // Pointer to tail
};

