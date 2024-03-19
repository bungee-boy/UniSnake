#pragma once


template <typename T> class LinkedList {
public:
	LinkedList();
private:
	struct ListNode {
		ListNode* m_prev{ nullptr };
		ListNode* m_next{ nullptr };
		T* m_data{ nullptr };
	};
	T* m_head;
	T* m_tail;
	
};

