#pragma once
#include<iostream>
#include "lstring.h"
#include "lqueue.h"
#include "lstack.h"
#include "tools.h"

template<typename T> class TreeNode {
public:
	T item;
	TreeNode<T>* lchild;
	TreeNode<T>* rchild;
	TreeNode<T>* parent;
	int height;
	TreeNode() :item(T()), lchild(nullptr), rchild(nullptr), parent(nullptr), height(1) {}
	TreeNode(const T& item) :item(item), lchild(nullptr), rchild(nullptr), parent(nullptr), height(1) {}
	TreeNode(const T& item, TreeNode<T>* lchild, TreeNode<T>* rchild, TreeNode<T>* parent) :item(item), lchild(lchild), rchild(rchild), parent(parent), height(calcuHeight()) {}
	TreeNode(const TreeNode<T>*& other) :item(other->item), lchild(other->lchild), rchild(other->rchild), parent(other->parent), height(other->height) {}

	void insertAsLeftChild(TreeNode<T>* other) {
		parent = other;
		lchild = other->lchild;
		if (other->hasLeft())other->lchild->parent = this;
		other->lchild = this;
		updateHeightAbove();
	}
	void insertAsRightChild(TreeNode<T>* other) {
		parent = other;
		rchild = other->rchild;
		if (other->hasRight())other->rchild->parent = this;
		other->rchild = this;
		updateHeightAbove();
	}

	bool isRoot()const {
		return parent == nullptr;
	}
	bool isLeaf()const {
		return (lchild == nullptr) && (rchild == nullptr);
	}
	bool isParent(TreeNode<T>* other);
	bool isLeftChild(TreeNode<T>* other)const { return parent == other && this == other->lchild; }
	bool isRightChild(TreeNode<T>* other)const { return parent == other && this == other->rchild;; }
	bool hasLeft()const { return lchild != nullptr; }
	bool hasRight()const { return rchild != nullptr; }
	int depth() {
		TreeNode<T>* p = this;
		int height = 0;
		while (p = p->parent) height++;
		return height;
	}
	int calcuHeight() const;
	void updateHeightAbove();

};
template<typename T> bool TreeNode<T>::isParent(TreeNode<T>* other){
	TreeNode<T>* p = other->parent;
	while (p) {
		if (p == this)
			return true;
		p = p->parent;
	}
	return false;
}
template<typename T> int TreeNode<T>::calcuHeight()const {
	if (isLeaf())return 1;
	if (!hasLeft()) return 1 + rchild->height;
	if (!hasRight()) return 1 + lchild->height;
	return 1 + lmax(rchild->height, lchild->height);
}
template<typename T> void TreeNode<T>::updateHeightAbove() {
	TreeNode<T>* p = this;
	while (p) {
		p->height = p->calcuHeight();
		p = p->parent;
	}
}
template<typename T> class lbintree {
protected:
	TreeNode<T>* _root;
	int _size;
	void init(int n, const T& item);
public:
	lbintree() :_root(nullptr), _size(0) {}
	lbintree(TreeNode<T>* node) :_root(node), _size(1) {}
	lbintree(int n) { init(n, T()); }
	lbintree(int n, const T& item) { init(n, item); }
	lbintree(const lbintree& other) :_root(other.root()), _size(other.size()) {}

	int size()const { return _size; }
	bool isEmpty() const { return _root == nullptr; }
	TreeNode<T>* root() { return _root;}

	TreeNode<T>* insertRootTakeLeft(const T& e);
	TreeNode<T>* insertRootTakeRight(const T& e);
	TreeNode<T>* insertAsLC(TreeNode<T>* node, const T& e);
	TreeNode<T>* insertAsRC(TreeNode<T>* node, const T& e);
	TreeNode<T>* insertAsLT(TreeNode<T>* node, lbintree<T>*& tree);
	TreeNode<T>* insertAsRT(TreeNode<T>* node, lbintree<T>*& tree);

	void insertLevel(T item);
	int remove(TreeNode<T>* node);
	int remove(const T& item);
	TreeNode<T>* find(T item);
	lvector<TreeNode<T>*> findAll(const T& item);
	TreeNode<T>*& getInLevel(int rank);
	T& operator[](int rank) { return getInLevel(rank)->item; }

	template<typename F> void traversePre(TreeNode<T>* node, F visit); // recursion
	template<typename F> void traversePost(TreeNode<T>* node, F visit); // recursion
	template<typename F> void traverseIn(TreeNode<T>* node, F visit); // recursion
	template<typename F> void traverseLevel(TreeNode<T>* node, F visit);

	template<typename F> void preTraverse(TreeNode<T>* node, F visit); // iteration
	template<typename F> void postTraverse(TreeNode<T>* node, F visit); // iteration
	template<typename F> void inTraverse(TreeNode<T>* node, F visit); // iteration
	
	void nullpointer(TreeNode<T>* node, lstring function);
	void print();
	void printLevel();
};

template<typename T> void lbintree<T>::init(int n, const T& item){
	_size = n;
	_root = new TreeNode<T>(item);
	TreeNode<T>* p = _root;
	lqueue<TreeNode<T>*> q;
	q.enqueue(_root);
	for (int i = 1; i < n; ){
		TreeNode<T>* node = q.dequeue();
		if ((!node->hasLeft())) {
			if (i == n) break;
			i++;
			TreeNode<T>* newNode = new TreeNode<T>(item);
			newNode->insertAsLeftChild(node);
			q.enqueue(newNode);
		}
		if (!node->hasRight()) {
			if (i == n) break;
			i++;
			TreeNode<T>* newNode = new TreeNode<T>(item);
			newNode->insertAsRightChild(node);
			q.enqueue(newNode);
		}
	}
}


template<typename T> TreeNode<T>* lbintree<T>::insertRootTakeLeft(const T& e) {
	_size += 1;
	TreeNode<T>* newnode = new TreeNode<T>(e);
	if (_root) _root->parent = newnode;
	newnode->lchild = _root;
	_root = newnode;
	return _root;
}
template<typename T> TreeNode<T>* lbintree<T>::insertRootTakeRight(const T& e)
{
	_size += 1;
	TreeNode<T>* newnode = new TreeNode<T>(e);
	if(_root) _root->parent = newnode;
	newnode->rchild = _root;
	_root = newnode;
	return _root;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsLC(TreeNode<T>* node, const T& e) {
	nullpointer(node, "insertAsLC");
	_size++;
	TreeNode<T>* newnode = new TreeNode<T>(e);
	newnode->insertAsLeftChild(node);
	return newnode;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsRC(TreeNode<T>* node, const T& e) {
	nullpointer(node, "insertAsRC");
	_size++;
	TreeNode<T>* newnode = new TreeNode<T>(e);
	newnode->insertAsRightChild(node);
	return newnode;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsLT(TreeNode<T>* node, lbintree<T>*& tree) {
	nullpointer(node, "insertAsLT");
	if (node->hasRight()) {
		std::cout << "Error in insertAsLT: This node has already had nodes as its left child!" << std::endl;
		exit(0);
	}
	_size += tree->size();
	node->lchild = tree->root();
	node->lchild->parent = node;
	node->lchild->updateHeightAbove();
	return node;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsRT(TreeNode<T>* node, lbintree<T>*& tree) {
	nullpointer(node, "insertAsRT");
	if (node->hasRight()) {
		std::cout << "Error in insertAsRT: This node has already had nodes as its right child!" << std::endl;
		exit(0);
	}
	_size += tree->size();
	node->rchild = tree->root();
	node->rchild->parent = node;
	node->rchild->updateHeightAbove();
	return node;
}

template<typename T> void lbintree<T>::insertLevel(T item){
	if (!_root) {
		insertRootTakeLeft(item);
		return;
	}
	lqueue<TreeNode<T>*> q;
	q.enqueue(_root);
	while (!q.isEmpty()) {
		TreeNode<T>* temp = q.dequeue();
		if (!temp->hasLeft()) {
			insertAsLC(temp, item);
			return;
		}
		else {
			if (!temp->hasRight()) {
				insertAsRC(temp, item);
				return;
			}
			q.enqueue(temp->lchild);
			q.enqueue(temp->rchild);
		}
	}
}

template<typename T> int lbintree<T>::remove(TreeNode<T>* node){
	int removalSize = 0;
	if (node == nullptr) return 0;
	if (node->parent != nullptr) {
		if (node == node->parent->lchild) node->parent->lchild = nullptr;
		if (node == node->parent->rchild) node->parent->rchild = nullptr;
	}
	lqueue<TreeNode<T>*> q;
	TreeNode<T>* p = node->parent;
	q.enqueue(node);
	while (!q.isEmpty()) {
		TreeNode<T>* temp = q.dequeue();
		if (temp){
			removalSize++;
			if (temp->hasLeft()) q.enqueue(temp->lchild);
			if (temp->hasRight()) q.enqueue(temp->rchild);
			temp->parent = nullptr; temp->lchild = nullptr; temp->rchild = nullptr;
			delete temp;
			temp = nullptr;
		}
	}
	if (p) p->updateHeightAbove();
	return removalSize;
}

template<typename T>int lbintree<T>::remove(const T& item){
	lvector<TreeNode<T>*> removals = findAll(item);
	std::cout << removals.size() << std::endl;
	return removals.size();
}

template<typename T> TreeNode<T>* lbintree<T>::find(T item){
	TreeNode<T>* res = nullptr;
	preTraverse(_root, [&](TreeNode<T>* p) {
		if (p->item == item)
			res = p;
		});
	return res;
}

template<typename T> lvector<TreeNode<T>*> lbintree<T>::findAll(const T& item){
	lvector<TreeNode<T>*> res;
	traverseLevel(_root, [&](TreeNode<T>* p) {
		if (p->item == item)
			res.push_back(p);
		});
	return res;
}

template<typename T> TreeNode<T>*& lbintree<T>::getInLevel(int rank) {
	try{
		if (rank >= _size || rank < 0)
			throw "Index Error In getInLevel";
	}
	catch (const char* errmsg){
		std::cout << errmsg << std::endl;
		exit(0);
	}
	int index = 0;
	TreeNode<T>* res = new TreeNode<T>;
	traverseLevel(_root, [&](TreeNode<T>* p) {
		if (index == rank){
			res = p;
			index++;
		}
		});
	return res;
}

template<typename T> template<typename F>
void lbintree<T>::traversePre(TreeNode<T>* node, F visit) {//middle->left->right
	if (!node)return;
	visit(node);
	traversePre(node->lchild, visit);
	traversePre(node->rchild, visit);
}
template<typename T> template<typename F>
void lbintree<T>::traversePost(TreeNode<T>* node, F visit) {//left->right->middle
	if (!node)return;
	traversePost(node->lchild, visit);
	traversePost(node->rchild, visit);
	visit(node);
}
template<typename T> template<typename F>
void lbintree<T>::traverseIn(TreeNode<T>* node, F visit) {//left->middle->right
	if (!node)return;
	traverseIn(node->lchild, visit);
	visit(node);
	traverseIn(node->rchild, visit);
}
template<typename T> template<typename F>
void lbintree<T>::traverseLevel(TreeNode<T>* node, F visit) {
	if (!node) return;
	lqueue<TreeNode<T>*> q;
	q.enqueue(node);
	while (!q.isEmpty()) {
		TreeNode<T>* temp = q.dequeue();
		visit(temp);
		if (temp->hasLeft())
			q.enqueue(temp->lchild);
		if (temp->hasRight())
			q.enqueue(temp->rchild);
	}
}


/*
* The iteration version of traverse uses some kind of "mark" to make the 
* program "knows" the the treenode is going to be visited rather than pushed.
* For the first time we visit the node, we add a nullptr as a notation that 
* the node should be visited in the next time, that is, the node before it is nullptr.
*/
template<typename T> template<typename F>
void lbintree<T>::preTraverse(TreeNode<T>* node, F visit){ // middle -> left -> right
	lstack<TreeNode<T>*> st;
	if (!node) return;
	st.push(node);
	TreeNode<T>* cur = node;
	while (!st.isEmpty()) {
		cur = st.pop(); // get the top node of the stack.
		if (cur) { // if the node is not nullptr, we should push it and its children to the stack
			if (cur->hasRight()) // right
				st.push(cur->rchild);
			if (cur->hasLeft()) // left
				st.push(cur->lchild);
			st.push(cur); // middle
			st.push(nullptr); //the nullptr will traverse all the nodes with the move of cur
		}
		else {// there is a nullptr node
			cur = st.pop(); // then we get the next node, that is the node we will visit.
			visit(cur);
		}
	}
}
template<typename T> template<typename F>
void lbintree<T>::postTraverse(TreeNode<T>* node, F visit){
	lstack<TreeNode<T>*> st;
	if (!node) return;
	st.push(node);
	TreeNode<T>* cur = node;
	while (!st.isEmpty()) {
		cur = st.pop(); // get the top node of the stack
		if(cur){ // the node is not a nullptr node 
			st.push(cur); // middle
			st.push(nullptr);
			if (cur->hasRight()) // right
				st.push(cur->rchild);
			if (cur->hasLeft()) // left
				st.push(cur->lchild);
		}
		else {
			cur = st.pop();
			visit(cur);
		}
	}
}
template<typename T> template<typename F>
void lbintree<T>::inTraverse(TreeNode<T>* node, F visit){
	lstack<TreeNode<T>*> st;
	if (!node) return;
	st.push(node);
	TreeNode<T>* cur = node;
	while (!st.isEmpty()) {
		cur = st.pop();
		if (cur) {
			if (cur->hasRight())
				st.push(cur->rchild);
			st.push(cur);
			st.push(nullptr); // add a virtual node after the real node
			if (cur->hasLeft())
				st.push(cur->lchild);
		}
		else {
			cur = st.pop();// the node after virtual node is the node that we will visit
			visit(cur);
		}
	}
}

template<typename T> void lbintree<T>::nullpointer(TreeNode<T>* node, lstring function){
	try {
		if (!node)
			throw "NullpointerException in " + function;
	}
	catch (lstring errmsg) {
		std::cout << errmsg << std::endl;
		exit(0);
	}
}

template<typename T> void lbintree<T>::print() {
	if (!_root) return;
	traversePre(_root, [](TreeNode<T>* p)->void {
		std::cout << p->item << "  ";
		if (p->parent) std::cout << "parent: " << p->parent->item << "  ";
		if (p->hasLeft())	std::cout << "lchild " << p->lchild->item << "  ";
		if (p->hasRight())	std::cout << "rchild " << p->rchild->item << "  ";
		std::cout << std::endl;
	});
	std::cout << std::endl;
	traversePre(_root, [](TreeNode<T>* p)->void {
		std::cout << p->height;
		}
	);
	std::cout << std::endl;
	preTraverse(_root, [](TreeNode<T>* p)->void {
		std::cout << p->item << "  ";
		if (p->parent) std::cout << "parent: " << p->parent->item << "  ";
		if (p->hasLeft())	std::cout << "lchild " << p->lchild->item << "  ";
		if (p->hasRight())	std::cout << "rchild " << p->rchild->item << "  ";
		std::cout << std::endl;
	});
	std::cout << std::endl;
	preTraverse(_root, [](TreeNode<T>* p)->void {
		std::cout << p->height;
		}
	);
	std::cout << std::endl;
}
template<typename T> void lbintree<T>::printLevel() {
	if (!_root) return;
	lqueue<TreeNode<T>*> q;
	q.enqueue(_root);
	while (!q.isEmpty()) {
		int qsize = q.size();
		for(int i = 0;i < qsize;i++){
			TreeNode<T>* temp = q.dequeue();
			std::cout << temp->item << "(" << temp->height << ")" << "   ";
			if (temp->hasLeft())
				q.enqueue(temp->lchild);
			if (temp->hasRight())
				q.enqueue(temp->rchild);
		}
		std::cout << std::endl;
	}
}