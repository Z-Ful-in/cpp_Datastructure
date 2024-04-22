#pragma once
#include<iostream>
#include "lqueue.h"
#include "tools.h"

template<typename T> class TreeNode {
public:
	T item;
	TreeNode<T>* lchild;
	TreeNode<T>* rchild;
	TreeNode<T>* parent;
	int height;
	TreeNode() :item(T()), lchild(nullptr), rchild(nullptr), parent(nullptr) {}
	TreeNode(const T& item) :item(item), lchild(nullptr), rchild(nullptr), parent(nullptr) {}
	TreeNode(const T& item, TreeNode<T>* lchild, TreeNode<T>* rchild, TreeNode<T>* parent) :item(item), lchild(lchild), rchild(rchild), parent(parent) {}
	TreeNode(const TreeNode<T>*& other) :item(other->item), lchild(other->lchild), rchild(other->rchild), parent(other->parent) {}

	void insertleft(TreeNode<T>* other) {
		parent = other;
		lchild = other->lchild;
		other->lchild = this;
	}
	void insertright(TreeNode<T>* other) {
		parent = other;
		rchild = other->rchild;
		other->rchild = this;
	}

	bool isRoot()const {
		return parent == nullptr;
	}
	bool isLeaf()const {
		return (parent != nullptr) && (lchild == nullptr) && (rchild == nullptr);
	}
	bool hasLeft()const { return lchild != nullptr; }
	bool hasRight()const { return rchild != nullptr; }
	int depth()const {
		TreeNode<T>* p = this;
		int height = 0;
		while (p = p->parent) height++;
		return height;
	}
	int height() const { return height; }
};
template<typename T> class lbintree {
protected:
	TreeNode<T>* _root;
	int _size;
	void init(int n, const T& item);
public:
	lbintree() :_root(new TreeNode<T>()), _size(0) {}
	lbintree(int n) { init(n, T()); }
	lbintree(int n, const T& item) { init(n, item); }

	int size()const { return _size; }
	int height(TreeNode<T>* p);
	void updateHeightAbove(TreeNode<T>* p);
	bool isEmpty() const { return _root == nullptr; }
	TreeNode<T>*& root() { return _root; }

	TreeNode<T>* insertAsRoot(const T& e);
	TreeNode<T>* insertAsLC(TreeNode<T>* node, const T& e);
	TreeNode<T>* insertAsRC(TreeNode<T>* node, const T& e);
	TreeNode<T>* insertAsLT(TreeNode<T>* node, lbintree<T>*& tree);
	TreeNode<T>* insertAsRT(TreeNode<T>* node, lbintree<T>*& tree);

	int remove(TreeNode<T>* node);

	template<typename F> void traversePre(TreeNode<T>* node, F visit);
	template<typename F> void traversePost(TreeNode<T>* node, F visit);
	template<typename F> void traverseIn(TreeNode<T>* node, F visit);
	template<typename F> void traverseLevel(TreeNode<T>* node, F visit);

	void print();
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
			newNode->insertleft(node);
			q.enqueue(newNode);
		}
		if (!node->hasRight()) {
			if (i == n) break;
			i++;
			TreeNode<T>* newNode = new TreeNode<T>(item);
			newNode->insertright(node);
			q.enqueue(newNode);
		}
	}
}
template<typename T> int lbintree<T>::height(TreeNode<T>* p) {
	if (!p) return 0;
	if (p->isLeaf())return 1;
	return 1 + lmax(height(p->lchild), height(p->rchild));
}
template<typename T> void lbintree<T>::updateHeightAbove(TreeNode<T>* p) {
	while (p) {
		p->height = height(p);
		p = p->parent;
	}
}

template<typename T> TreeNode<T>* lbintree<T>::insertAsRoot(const T& e) {
	_size = 1;
	_root = new TreeNode<T>(e);
	return _root;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsLC(TreeNode<T>* node, const T& e) {
	_size++;
	TreeNode<T>* newnode = new TreeNode<T>(e);
	newnode->insertleft(node);
	return newnode;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsRC(TreeNode<T>* node, const T& e) {
	_size++;
	TreeNode<T>* newnode = new TreeNode<T>(e);
	newnode->insertright(node);
	return newnode;
}
template<typename T> TreeNode<T>* lbintree<T>::insertAsLT(TreeNode<T>* node, lbintree<T>*& tree) {
	_size += tree->size();
	node->lchild = tree->root();
	node->lchild->parent = node;
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
	traversePre(node->lchild, visit);
	traversePre(node->rchild, visit);
	visit(node);
}
template<typename T> template<typename F>
void lbintree<T>::traverseIn(TreeNode<T>* node, F visit) {//left->middle->right
	if (!node)return;
	traversePre(node->lchild, visit);
	visit(node);
	traversePre(node->rchild, visit);
}
template<typename T> template<typename F>
void lbintree<T>::traverseLevel(TreeNode<T>* node, F visit) {
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

template<typename T> void lbintree<T>::print() {
	traverseLevel(_root, [](TreeNode<T>* p)->void {std::cout << p->item << "  "; });
}