#pragma once
#include "llist.h"

template<typename T> class lqueue :public llist<T> {
public:
	void enqueue(const T& e) {
		llist<T>::insertAsLast(e);
	}
	T dequeue() {
		if (llist<T>::isEmpty()) return T();
		Node<T>* removeNode = llist<T>::remove(llist<T>::header->next);
		return removeNode->item;
	}
	T& front() {
		if (llist<T>::isEmpty())return T();
		return llist<T>::header->next->item;
	}
};