#pragma once
#include<iostream>
#include "tools.h"
template<typename T>class Node {
public:
	T item;
	Node<T>* prev;
	Node<T>* next;
	Node() :item(T{}), prev(nullptr), next(nullptr) {}
	Node(T value):item(value),prev(nullptr),next(nullptr){}
	Node(T value, Node<T>* prev, Node<T>* next) :item(value), prev(prev), next(next) {}
	Node(const Node& node) {
		item = node->prev;
		next = node->next;
		prev = node->prev;
	}

	void insertB(Node<T>* node);
	void insertA(Node<T>* node);
};
template<typename T> void Node<T>::insertA(Node<T>* node) {
	if (node->next == nullptr) {
		node->next = this;
		prev = node;
		next = nullptr;
	}
	else {
		node->next->prev = this;
		next = node->next;
		prev = node;
		node->next = this;
	}
}
template<typename T> void Node<T>::insertB(Node<T>* node) {
	if (node->prev == nullptr) {
		next = node;
		prev = nullptr;
		node->prev = this;
	}
	else {
		next = node;
		prev = node->prev;
		node->prev->next = this;
		node->prev = this;
	}
}

template<typename T> class llist {
protected:
	int _size;
	Node<T>* header;
	Node<T>* trailer;

	void selectionSort(Node<T>*p, int n);
	void insertionSort(Node<T>*p, int n);
	void bubbleSort(Node<T>*p, int n);
	void quickSort(Node<T>*p, int n);
	void mergeSort(Node<T>*p, int n);
public:
	class iterator {
		llist<T>* parent;
		int index;
	public:
		iterator(llist<T>* item, int index) : parent(item), index(index) {}
		iterator& operator++();
		bool operator!=(const iterator& other);
		Node<T>* operator*();
	};
	llist();
	llist(int n, T item);
	llist(const llist& other);
	~llist();

	iterator begin() { return iterator(this, 0); }
	iterator end() { return iterator(this, _size); }
	
	//helper method
	void init();
	void print()const;

	int rankchange(int rank)const;
	bool rankcheck(int rank)const;
	bool rangecheck(int lo, int hi)const;
	void sortcheck() const;
	bool isSorted()const { return isSorted(header->next, _size); }
	bool isSorted(Node<T>* p, int n)const;
	Node<T>* getMaxNode(Node<T>* p, int n)const;
	Node<T>* getMaxNode()const { return getMaxNode(header->next, _size); }

	int size()const { return _size; }
	bool isEmpty() const { return _size == 0 };
	Node<T>* getheader()const { return header; }
	Node<T>* gettrailer()const { return trailer; }

	Node<T>*& lget(int rank)const;
	Node<T>*& operator[](int rank)const { return lget(rank); }
	T insert(int rank, const T& item);
	T insertAsLast(const T& item);
	T insertAsFirst(const T& item);
	int remove(int lo, int hi);
	Node<T>* remove(Node<T>* p, int n);
	void remove(int rank);
	Node<T>* remove(Node<T>* p);

	void reverse();
	void sort();

	int search(const T& target, Node<T>*p, int n)const;
	int search(const T& target)const { return search(target, header->next, _size); }
	int find(const T& target, Node<T>*p, int n)const;
	int find(const T& target)const { return find(target, header->next, _size); }

	void deduplicate(Node<T>*p, int n);
	void deduplicate() { deduplicate(header->next, _size); }
	void uniquify(Node<T>*p, int n);
	void uniquify() { uniquify(header->next, _size); }
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
template<typename T> llist<T>::llist(const llist<T>& other) {
	_size = other.size();
	init();
	Node<T>* p = other.getheader();
	while ((p=p->next) != other.getheader()) {
		Node<T>* node = new Node<T>(p->item, trailer, trailer->prev);
		trailer->prev->next = node;
		trailer->prev = node;
	}
}
template<typename T> llist<T>::~llist() {
	while (header != trailer) {
		header = header->next;
		delete header->prev;
	}
	delete trailer;
}

template<typename T> bool llist<T>::rankcheck(int rank)const {
	try{
		if (rank > _size || rank <= 0)
			throw "IndexERROR!";
	}
	catch (const char* errmsg){
		std::cout << errmsg << std::endl;
		return false;
	}
	return true;
}
template<typename T> int llist<T>::rankchange(int rank)const {
	return rank < 0 ? 0 : (rank >= _size ? _size-1 : rank);
}
template<typename T> bool llist<T>::rangecheck(int lo, int hi)const {
	try{
		if (!(lo < _size && hi>0 && lo < hi))
			throw "indexERROR in rangecheck";
	}
	catch (const char*errmsg){
		std::cout << errmsg << std::endl;
		return false;
	}
	return true;
}
template<typename T> void llist<T>::sortcheck() const
{
	try {
		if (!isSorted())
			throw "The List is Not Sorted!";
	}
	catch (const char* errmsg) {
		std::cout << errmsg << std::endl;
		exit(0);
	}
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
template<typename T> Node<T>*& llist<T>::lget(int rank)const {
	if (!rankcheck(rank + 1))
		exit(0);
	Node<T>* p = header->next;
	while (rank-- && p->next != trailer)
		p = p->next;
	return p;
}
template<typename T> bool llist<T>::isSorted(Node<T>* p, int n) const{
	while (--n) {
		if (p->item > p->next->item)
			return false;
		p = p->next;
	}
	return true;
}
template<typename T> Node<T>* llist<T>::getMaxNode(Node<T>* p, int n)const {
	T result = p->item;
	Node<T>* record = p;
	while ((--n) && ((p = p->next) != trailer)) {
		if (result <= p->item) {
			result = p->item;
			record = p;
		}
	}
	return record;
}

template<typename T> T llist<T>::insert(int rank, const T& item) {
	rank = rankchange(rank);
	_size++;
	Node<T>* p = header;
	while (rank--) {
		p = p->next;
	}
	Node<T>* newnode = new Node<T>(item);
	newnode->insertA(p);
	return item;
}
template<typename T> T llist<T>::insertAsFirst(const T& item) {
	_size++;
	Node<T>* node = new Node<T>(item);
	node->insertA(header);
	return item;
}
template<typename T> T llist<T>::insertAsLast(const T& item) {
	_size++;
	Node<T>* node = new Node<T>(item);
	node->insertB(trailer);
	return item;
}
template<typename T> int llist<T>::remove(int lo, int hi) {
	if (!rangecheck(lo, hi))
		exit(0);
	lo = rankchange(lo);
	hi = rankchange(hi);
	int length = hi - lo;
	Node<T>* p = header;
	Node<T>* temp = new Node<T>();
	for (int i = 0; i < hi; i++) {
		p = p->next;
		if (i == lo) {
			temp = p->prev;
		}
		else if (i > lo) {
			delete p->prev;
		}
	}
	p = p->next;
	delete p->prev;
	temp->next = p;
	p->prev = temp;
	_size -= length;
	return length;
}
template<typename T> void llist<T>::remove(int rank) {
	remove(rank, rank + 1);
}
template<typename T> Node<T>* llist<T>::remove(Node<T>* p, int n) {
	Node<T>* returnNode = p;
	_size -= n;
	while (n--) {
		p->prev->next = p->next;
		p->next->prev = p->prev;
		p = p->next;
	}
	return returnNode;
}
template<typename T> Node<T>* llist<T>::remove(Node<T>* p) {
	return remove(p, 1);
}

template<typename T> void llist<T>::reverse() {
	Node<T>* p = header;
	while (p != trailer) {
		if (p == header) {
			p->prev = p->next;
			p->next = nullptr;
			p = p->prev;
		}
		else {
			Node<T>* temp = p->prev;
			p->prev = p->next;
			p->next = temp;
			p = p->prev;
		}
	}
	p->next = p->prev;
	p->prev = nullptr;
	trailer = header;
	header = p;
}


template<typename T> int llist<T>::search(const T& target, Node<T>* p, int n) const
{
	sortcheck();
	for (int i = 0; i < n; i++){
		if (p->item < target) {
			p = p->next;
		}
		else if ((p->item > target) && ((!i) || (p->prev->item < target))){
			return -1; 
		}
		else {
			return i;
		}
	}
}
template<typename T> int llist<T>::find(const T& target, Node<T>* p, int n) const{
	if (isSorted())
		std::cout << "List is Sorted, recommend to use function: \"search\"" << std::endl;
	for (int i = 0; i < n; i++){
		if (p->item == target)
			return i;
		p = p->next;
	}
	return -1;
}
template<typename T> void llist<T>::deduplicate(Node<T>* p, int n){
	sortcheck(); //sorted
	Node<T>* temp = p->next;
	while (--n) {
		if (p->item != temp->item) {
			p->next = temp;
			temp->prev = p;
			p = temp;
			temp = temp->next;
		}
		else {
			_size--;
			temp = temp->next;
			delete temp->prev;
		}
	}
}
template<typename T> void llist<T>::uniquify(Node<T>* p, int n){
	if (isSorted(p , n))
		std::cout << "List is Sorted, recommend to use function: \"deduplicate\"" << std::endl;
	int record = 0;
	Node<T>* endNode = p;
	for (int i = 0; i < n; i++, endNode = endNode->next);
	while (--n && p!=endNode) {
		Node<T>* temp = p->next;
		while (temp != endNode) {
			temp = temp->next;
			if (p->item == temp->prev->item) {
				remove(temp->prev);
			}
		}
		p = p->next;
	}
}

template<typename T> void llist<T>::selectionSort(Node<T>* p, int n) {
	if (n <= 1)return;
	Node<T>* endNode = p;
	int record = n;
	while (--record && ((endNode = endNode->next) != trailer));
	while (n != 1) {
		Node<T>* maxNode = getMaxNode(p, n--);
		lswap(maxNode->item, endNode->item);
		endNode = endNode->prev;
	}
}
template<typename T> void llist<T>::insertionSort(Node<T>* p, int n) {
	Node<T>* temp = p;
	while (n--) {
		temp = temp->next;
		p = temp->prev;
		while (p = p->prev) {
			if ((p == header) || (p->item <= temp->prev->item)) {
				Node<T>* insertNode = temp->prev;
				temp->prev = insertNode->prev;
				insertNode->prev->next = temp;
				insertNode->insertA(p);
				break;
			}
		}
	}
}
template<typename T> void llist<T>::bubbleSort(Node<T>* p, int n) {
	Node<T>* temp = p;
	while (n--) {
		p = temp;
		for (int j = 0; j < n; j++) {
			if (p->item >= p->next->item)
				lswap(p->item, p->next->item);
			p = p->next;
		}
	}
}
template<typename T> void llist<T>::mergeSort(Node<T>* p, int n){
	if (n <= 1) return;
	Node<T>* result = p;
	for (int i = 0; i < n/2; i++)
		p = p->next;
	mergeSort(result, n / 2);
	mergeSort(p, n - n / 2);
	Node<T>* temp0 = new Node<T>();
	Node<T>* temp1 = p->prev;
	for (int i = 0; i < n / 2; i++) {
		Node<T>* node = new Node<T>(temp1->item);
		node->insertA(temp0);
		temp1 = temp1->prev;
	} // construct a llist starting with temp0
	int tempindex = 0;
	int pindex = 0;
	temp0 = temp0->next;
	for (int i = 0; i < n; i++){
		if ((pindex == (n - n / 2)) || ((tempindex != n / 2) && (temp0->item <= p->item))) {
			tempindex++;
			result->item = temp0->item;
			result = result->next;
			temp0 = temp0->next;
		}
		else {
			pindex++;
			result->item = p->item;
			result = result->next;
			p = p->next;
		}
	}
	delete temp0;
}
template<typename T> void llist<T>::quickSort(Node<T>* p, int n) {
	if (n <= 1)return;
	Node<T>* temp = p->next;
	Node<T>* newheader = p;
	Node<T>* endNode = p;
	int bigrecord = 0, smallrecord = 0;
	for (int i = 0; i < n; i++, endNode = endNode->next);
	while (temp != endNode) {
		temp = temp->next;
		Node<T>* insertNode = temp->prev;
		temp->prev = insertNode->prev;
		insertNode->prev->next = temp;
		if (insertNode-> item <= p->item) {
			insertNode->insertB(p);
			smallrecord++;
			if (smallrecord == 1) newheader = insertNode;
		}
		else {
			insertNode->insertA(p);
			bigrecord++;
		}
	}
	quickSort(newheader, smallrecord);
	quickSort(p->next, bigrecord);
}
template<typename T> void llist<T>::sort() {
	mergeSort(header->next, _size);
}

template<typename T> typename llist<T>::iterator& llist<T>::iterator::operator++()
{
	index++;
	return *this;
}
template<typename T> bool llist<T>::iterator::operator!=(const iterator& other)
{
	return index < other.index;
}
template<typename T> Node<T>* llist<T>::iterator::operator*()
{
	return parent->lget(index);
}
