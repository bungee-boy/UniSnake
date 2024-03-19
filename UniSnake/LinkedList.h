#pragma once
#include <iostream>

template <typename T> struct ListNode {  // Linked list node
	ListNode* prev{ nullptr };  // Pointer to prev
	ListNode* next{ nullptr };  // Pointer to next
	T data;  // Data of the node
};

template <typename T> class LinkedList {
public:
	LinkedList() {};  // Default constructor
	~LinkedList();  // Default deconstructor
	ListNode<T>* getHead();  // Get head ptr
	ListNode<T>* getTail();  // Get tail ptr
	void push_front(const T& data);  // Add a new node to head
	void pop_front();  // Delete a node from head 
	void push_back(const T& data);  // Add node to tail
	void pop_back();
private:
	ListNode<T>* m_head{ nullptr };  // Pointer to head
	ListNode<T>* m_tail{ nullptr };  // Pointer to tail
	
};

