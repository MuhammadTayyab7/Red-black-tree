#pragma once
template<class T>
struct Node
{
	T data;
	Node<T>* left;
	Node<T>* right;
	Node<T>* father;
	char colour;
};