#include "LinkedList.h"

template <typename T> LinkedList<T>::~LinkedList() {
	while (m_head != nullptr)  // Cleanup all nodes from memory
		pop_back();
}

template <typename T> void LinkedList<T>::push_front(const T& data) {
	ListNode* newNode = new ListNode{ nullptr, nullptr, data };  // Create new node

	if (m_head == nullptr)  // If list is empty
		m_head = newNode;  // Set to head
	else {  // Add to head
		newNode->m_next = m_head;  // Point new to head (N -> H)
		m_head->m_prev = newNode;  // Point head to new (N <- H)
		m_head = newNode;  // Set head to new
	}
}

template <typename T> void LinkedList<T>::push_back(const T& data) {
	ListNode* newNode = new ListNode{ nullptr, nullptr, data };  // Create new node

	if (m_head == nullptr)  // If list is empty
		m_head = newNode;  // Set to head
	else {  // Add to tail
		if (m_tail == nullptr) {  // If tail is none
			m_head->m_next = newNode;  // Point head to tail (H -> T)
			newNode->m_prev = m_head;  // Point tail to head (H <- T)
			m_tail = newNode;  // Set tail
		}
		else {  // Tail exists
			m_tail->m_next = newNode;  // Point tail to new (T -> N)
			newNode->m_prev = m_tail;  // Point new to tail (T <- N)
			m_tail = newNode;  // Set tail to new
		}
	}
}

template <typename T> void LinkedList<T>::pop_front() {
	if (m_head == nullptr && m_tail != nullptr) {  // If only tail (should never happen!)
		delete m_tail;  // Fix error
		m_tail = nullptr;
		std::cerr << "WARN -> LinkedList::pop_front() Head was nullptr while Tail was not!\n";
	}
	else if (m_head != nullptr) {  // If head exists
		m_head = m_head->m_next;
		delete m_head->m_prev;
		m_head->m_prev = nullptr;
		if (m_head == m_tail)  // If head and tail are same
			m_tail = nullptr;  // Don't delete but set tail to null
	}
	else
		std::cerr << "WARN -> LinkedList::pop_front() called when list is empty!\n";
}

template <typename T> void LinkedList<T>::pop_back() {
	if (m_tail == nullptr && m_head != nullptr) {  // If only head
		delete m_head;  // Delete head
		m_head = nullptr;
	}
	else if (m_tail != nullptr) {  // If tail exists
		m_tail = m_tail->m_prev;  // Remove tail
		delete m_tail->m_next;
		m_tail->m_next = nullptr;
		if (m_tail == m_head)  // If head and tail are same
			m_tail = nullptr;  // Don't delete but set tail to null
	}
	else
		std::cerr << "WARN -> LinkedList::pop_back() called when list is empty!\n";
}
