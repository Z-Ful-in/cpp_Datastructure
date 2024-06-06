#pragma once
#include"lbintree.hpp"
#include"lvector.hpp"
#include"lstack.hpp"

template<typename T>class BST : public lbintree<T> {
public: 
	using lbintree<T>::_root;
	using lbintree<T>::_size;
	using lbintree<T>:: lbintree;
	using lbintree<T>::insertRootTakeLeft;
	BST() : lbintree() {}
	BST(const lvector<T>& other);

	virtual TreeNode<T>* insert(const T& item);
	virtual TreeNode<T>* remove(int index); // remove preOrder
	virtual TreeNode<T>* remove(TreeNode<T>* node);
	virtual TreeNode<T>*& search(const T& item);
};

template<typename T> BST<T>::BST(const lvector<T>& other) {
	_root = nullptr;
	_size = 0;
	int index = 0;
	while (index < other.size())
		insert(other[index++]);
}

template<typename T> TreeNode<T>* BST<T>::insert(const T& val){
	if (!_root) return insertRootTakeLeft(val);
	TreeNode<T>* p = _root;
	_size++;
	TreeNode<T>* newnode = new TreeNode<T>(val);
	while (p) {
		if (p->item > val) {
			if(p->hasLeft()) p = p->lchild;
			else {
				newnode->insertAsLeftChild(p);
				break;
			}
		}
		else {
			if (p->hasRight()) p = p->rchild;
			else {
				newnode->insertAsRightChild(p);
				break;
			}
		}
	}
	newnode->updateHeightAbove();
	return newnode;
}

template<typename T> TreeNode<T>* BST<T>::remove(int index){
	if (!_root) return nullptr;
	if (index >= _size || index < 0) {
		std::cout << "index is out of boundary in lBST::remove(int index)!" << std::endl;
		return nullptr;
	}
	TreeNode<T>* p = _root;
	lstack<TreeNode<T>*> st;
	st.push(p);
	TreeNode<T>* cur = nullptr;
	while (index+1) {
		cur = st.pop();
		if (cur) {
			if (cur->hasRight()) st.push(cur->rchild);
			st.push(cur);
			st.push(nullptr);
			if (cur->hasLeft()) st.push(cur->lchild);
		}
		else {
			cur = st.pop();
			index--;
		}
	}
	return remove(cur);
}

template<typename T> TreeNode<T>* BST<T>::remove(TreeNode<T>* node){ //ERROR TODO
	_size -= 1;
	if (node->isLeaf()) {
		if (node->isLeftChild(node->parent)) node->parent->lchild = nullptr;
		else if (node->isRightChild(node->parent)) node->parent->rchild = nullptr;
		return node;
	}
	if (node->hasRight()) {
		TreeNode<T>* cur = node->rchild;
		TreeNode<T>* minNode = cur;
		while (minNode->hasLeft()) // get the minium node of the right tree
			minNode = minNode->lchild;
		if(node->hasLeft()) node->lchild->parent = minNode;
		minNode->lchild = node->lchild;
		node->rchild->parent = node->parent;
		if(node->isLeftChild(node->parent))node->parent->lchild = cur;
		else if (node->isRightChild(node->parent))node->parent->rchild = cur;
		minNode->updateHeightAbove();
	}
	else {
		TreeNode<T>* cur = node->lchild;
		node->lchild->parent = node->parent;
		if (node->isLeftChild(node->parent)) node->parent->lchild = cur;
		else if (node->isRightChild(node->parent)) node->parent->rchild = cur;
		cur->updateHeightAbove();
	}
	return node;
}
/*
*							20
*			15							25	
*	10				17				22				27
*5		13		16		19		21		24		26		28
*/

template<typename T> TreeNode<T>*& BST<T>::search(const T& val){
	TreeNode<T>* p = _root;
	while (p && p->item != val) {
		if (p->item > val) p = p->rchild;
		else p = p->lchild;
	}
	return p;
}

// left - middle - right 
//						20
//			15						25
//  10			18			23         30
//9   11      16   19