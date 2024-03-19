#pragma once
#include <iostream>

template <typename T> class LinkedList {
public:
	LinkedList() {};  // Default constructor
	~LinkedList();  // Default deconstructor
	void push_front(const T& data);  // Add a new node to head
	void pop_front();  // Delete a node from head
	void push_back(const T& data);  // Add node to tail
	void pop_back();
private:
	struct ListNode {
		ListNode* m_prev{ nullptr };  // Pointer to prev
		ListNode* m_next{ nullptr };  // Pointer to next
		T m_data;  // Data of the node
	};
	ListNode* m_head;  // Pointer to head
	ListNode* m_tail;  // Pointer to tail
	
};

