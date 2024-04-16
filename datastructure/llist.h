#pragma once
#include<iostream>
template<typename T>class Node {
public:
	T item;
	Node<T>* prev;
	Node<T>* next;
	Node() :item(T{}), prev(nullptr), next(nullptr) {}
	Node(T value, Node<T>* prev, Node<T>* next) :item(value), prev(prev), next(next) {}
};
template<typename T> class llist {
private:
	int _size;
	Node<T>* header;
	Node<T>* trailer;
public:
	void init();
	llist();
	llist(int n, T item);
	~llist();


	void print()const;
};

template<typename T> void llist<T>::init() {
	_size = 0;
	header = new Node<T>();
	trailer = new Node<T>();
	header->prev = nullptr;
	header->next = trailer;
	trailer->prev = header;
	trailer->next = nullptr;
}

template<typename T> llist<T>::llist() {
	init();
}
template<typename T> llist<T>::llist(int n, T item) {
	init();
	for (int i = 0; i < n; i++){
		Node<T>* node = new Node<T>(item, trailer->prev, trailer);
		trailer->prev->next = node;
		trailer->prev = node;
		_size++;
	}
}
template<typename T> llist<T>::~llist() {
	while (header != trailer) {
		header = header->next;
		delete header->prev;
	}
	delete trailer;
}

template<typename T> void llist<T>::print()const {
	Node<T>* p = header->next;
	while (p != trailer) {
		std::cout << p->item;
		if (p->next != trailer) std::cout << " -->";
		p = p->next;
	}
	std::cout << std::endl;
}