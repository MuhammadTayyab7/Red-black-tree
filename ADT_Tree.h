#pragma once
#include"Node.h"
template<class T>
class ADT_Tree
{
protected:
	Node<T>* root;
public:
	ADT_Tree();
	virtual void insert(T) = 0;
	virtual void SearchByValue(T) = 0;
	virtual void DestroyallTree() = 0;
	virtual void FindParent(T) = 0;
	virtual void inorder1() = 0;
	virtual void preorder1() = 0;
	virtual void postorder1() = 0;
	virtual void inorder2() = 0;
	virtual void preorder2() = 0;
	virtual void postorder2() = 0;
	~ADT_Tree();
};

template<class T>
ADT_Tree<T>::ADT_Tree()
{
	this->root = nullptr;
}

template<class T>
ADT_Tree<T>::~ADT_Tree()
{
	if (this->root != nullptr)
	{
		this->root = nullptr;
		delete[]root;
	}
}
