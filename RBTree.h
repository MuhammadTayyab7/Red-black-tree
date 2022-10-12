#pragma once
#include"ADT_Tree.h"
#include<iostream>
using namespace std;
template<class T>
class RBTree :public ADT_Tree<T>
{
private://wrapper functions
	void insertBST(Node<T>*& n, T value);//insert values according to BST(binary search tree rules).
	void fixRBTree(Node<T>*& n);//check the inserted node and do colouring and rotation.(Red black properties)
	void LRrotate(Node<T>*& gp, Node<T>*& p, Node<T>*& n);
	void RLrotate(Node<T>*& gp, Node<T>*& p, Node<T>*& n);
	void LLrotate(Node<T>*& gp, Node<T>*& p);
	void RRrotate(Node<T>*& gp, Node<T>*& p); //Right rotate
	Node<T>* getUncle(Node<T>*& n,Node<T>*& p,Node<T>*& gp);//find uncle 
	Node<T>* Search_node(Node<T>*& n, T value);//Search value from the existing tree
	void destroy(Node<T>*& n);//Destory all tree
	void getParent(Node<T>* n, T value);//find father of given node
	void recolour(Node<T>* n);//Recolouring
	void INORDER1(Node<T>* n);     //---->LNR
	void PREORDER1(Node<T>* n);    //---->NLR
	void POSTORDER1(Node<T>* n);   //---->LRN
	void INORDER2(Node<T>* n);     //---->RNL
	void PREORDER2(Node<T>* n);    //---->NRL
	void POSTORDER2(Node<T>* n);   //---->RLN
public:
	void insert(T value);
	void SearchByValue(T value);
	void DestroyallTree();
	void FindParent(T value);
	void inorder1();
	void preorder1();
	void postorder1();
	void inorder2();
	void preorder2();
	void postorder2();
	/*RBTree() {
		this->root = nullptr;
	}*/
};
//wrapper functions 
template<class T>
void RBTree<T>::insertBST(Node<T>*& n, T value)
{ //n is root
	Node<T>* newNode = new Node<T>;
	newNode->data = value;
	newNode->father = nullptr;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->colour = 'R';
	Node<T>* dublicate;
	if (n != nullptr)
	{
		dublicate = Search_node(n, value);
		if (dublicate == nullptr)
		{
			goto l1;
		}
		if (newNode->data == dublicate->data)
		{
			cout << "Dublicate value is not allow to insert in BST." << endl;
			return;
		}
	}
	else
	{
	  l1:
		if (n == nullptr)
		{
			n = newNode;
			n->colour = 'B';
		}
		else
		{
			while (1)
			{
				if (value < n->data)//value less than current node value
				{
					if (n->left == nullptr)
					{
						newNode->father = n;
						n->left = newNode;
						if (newNode->father == nullptr)//if node parent is nullptr
						{
							newNode->colour = 'B';
							return;
						}
						if (newNode->father->father == nullptr)//if grand parent is nullptr
						{
							return;
						}
						fixRBTree(n->left);
						break;
					}
					else
					{
						n = n->left;
					}
				}
				else//value greater than current node value
				{
					if (n->right == nullptr)
					{
						newNode->father = n;
						n->right = newNode;
						if (newNode->father == nullptr)//if node parent is nullptr
						{
							newNode->colour = 'B';
							return;
						}
						if (newNode->father->father == nullptr)//if grand parent is nullptr
						{
							return;
						}
						fixRBTree(n->right);
						break;
					}
					else
					{
						n = n->right;
					}

				}
			}
		}
	}
	
}
template<class T>
void RBTree<T>::fixRBTree(Node<T>*& n)
{
	Node<T>* parent = n->father;
	Node<T>* grandParent = n->father->father;
	if (parent->colour == 'B')
	{
		return;
	}
	else
	{
		Node<T>* uncle = nullptr;
		uncle = getUncle(n,parent,grandParent);
		if (uncle == nullptr || uncle->colour == 'B')
		{
			if (grandParent->right != nullptr && parent->right != nullptr && parent->right->data 
				== n->data && grandParent->right->data == parent->data)
			{
				RRrotate(grandParent, parent);
				recolour(grandParent);
				recolour(parent);
				return;
			}
			if (grandParent->left != nullptr && parent->left != nullptr && parent->left->data 
				== n->data && grandParent->left->data == parent->data)
			{
				LLrotate(grandParent, parent);
				recolour(grandParent);
				recolour(parent);
				return;

			}
			if (grandParent->left != nullptr && parent->right != nullptr && parent->right->data 
				== n->data && grandParent->left->data == parent->data)
			{
				LRrotate(grandParent, parent, n);
				recolour(grandParent);
				recolour(n);
				return;
			}
			if (grandParent->right != nullptr && parent->left != nullptr && parent->left->data 
				== n->data && grandParent->right->data == parent->data)
			{
				RLrotate(grandParent, parent, n);
				recolour(grandParent);
				recolour(n);
				return;
			}
		}
		else
		{
			cout << "root" << this->root->data << endl;
			if (grandParent != this->root)
			{
				recolour(grandParent);
			}
			recolour(uncle);
			recolour(parent); 
		}
	}
}
template<class T>
void RBTree<T>::LRrotate(Node<T>*& gp, Node<T>*& p, Node<T>*& n)
{
	gp->left = n;
	p->right = n->left;
	n->left = p;
	LLrotate(gp, n);
}
template<class T>
void RBTree<T>::RLrotate(Node<T>*& gp, Node<T>*& p, Node<T>*& n)
{
	gp->right = n;
	p->left = nullptr;
	n->right = p;
	RRrotate(gp, n);
}
template<class T>
void RBTree<T>::LLrotate(Node<T>*& gp, Node<T>*& p)
{
	Node<T>* gpp = nullptr;
	gpp = gp->father;
	if (gpp != nullptr)
	{
		if (gpp->left != nullptr && gpp->left->data == gp->data)
		{
			gpp->left = p;
		}
		else if (gpp->right != nullptr && gpp->right->data == gp->data)
		{
			gpp->right = p;
		}
	}
	p->right = gp;
	gp->left = nullptr;
	
}
template<class T>
void RBTree<T>::RRrotate(Node<T>*& gp, Node<T>*& p)
{
	Node<T>* gpp = nullptr;
	gpp = gp->father;
	if (gpp != nullptr)
	{
		if (gpp->left != nullptr && gpp->left->data == gp->data)
		{
			gpp->left = p;
		}
		else if (gpp->right != nullptr && gpp->right->data == gp->data)
		{
			gpp->right = p;
		}
	}	
	p->left = gp;
	gp->right = nullptr;

}
template<class T>
Node<T>* RBTree<T>::getUncle(Node<T>*& n,Node<T>*& p,Node<T>*& gp)
{
	if (gp != nullptr)
	{
		if (gp->right != nullptr && gp->right->data == p->data) 
		{
			return gp->left;
		}
		if (gp->left != nullptr && gp->left->data == p->data)
		{
			return gp->right;
		}
		return nullptr;
	}
	else 
		return nullptr;
}
template<class T>
Node<T>* RBTree<T>::Search_node(Node<T>*& n, T value)
{
	if (n != nullptr)
	{
		if (value == n->data)
		{
			return n;
		}
		else if (value < n->data)
		{
			return Search_node(n->left, value);
		}
		else if (value > n->data)
		{
			return Search_node(n->right, value);
		}
	}
	else
		return n;
}
template<class T>
void RBTree<T>::destroy(Node<T>*& n)
{
	if (n == nullptr)
	{
		return;
	}
	destroy(n->left);
	destroy(n->right);
	n->left = nullptr;
	n->right = nullptr;
	n->data = 0;
	n->colour = NULL;
	delete n->left;
	delete n->right;
	delete n;
	n = nullptr;
}
template<class T>
void RBTree<T>::getParent(Node<T>* n, T value)
{
	Node<T>* temp = Search_node(n, value);
	if (temp != nullptr)
	{
		if (this->root->data == temp->data)
		{
			cout << "This is root Node (Root node has no father)." << endl;
		}
		else
		{
			Node<T>* p = temp->father;
			cout << p->data;
			cout << "->(" << p->colour << ") ";
		}
	}
	else
	{
		cout << "Node you entered not present in Tree..." << endl;
	}
}
template<class T>
void RBTree<T>::recolour(Node<T>* n)
{
	if (n->colour == 'B')
	{
		n->colour = 'R';
	}
	else
	{
		n->colour = 'B';
	}
}
template<class T>
void RBTree<T>::INORDER1(Node<T>* n)//LNR
{
	if (n != nullptr)// this check is the base case of this recursive function it will terminate if the sent node is a nullptr;
	{
		// now you know that the node has something to its left or right;
		//For Inorder, you traverse from the left subtree to the root then to the right subtree.
		INORDER1(n->left);
		cout << n->data;
		cout << "->(" << n->colour << ") ";
		INORDER1(n->right);
	}
}
template<class T>
void RBTree<T>::PREORDER1(Node<T>* n)//NLR
{
	if (n != nullptr)// this check is the base case of this recursive function it will terminate if the sent node is a nullptr;
	{
		// now you know that the node has something to its left or right;
		//For Preorder, you traverse from the root to the left subtree then to the right subtree.
		cout << n->data;
		cout << "->(" << n->colour << ") ";
		PREORDER1(n->left);
		PREORDER1(n->right);
	}
}
template<class T>
void RBTree<T>::POSTORDER1(Node<T>* n)//LRN
{
	if (n != nullptr)// this check is the base case of this recursive function it will terminate if the sent node is a nullptr;
	{
		// now you know that the node has something to its left or right;
		//For Post order, you traverse from the left subtree to the right subtree then to the root.
		POSTORDER1(n->left);
		POSTORDER1(n->right);
		cout << n->data;
		cout << "->(" << n->colour << ") ";
	}
}
template<class T>
void RBTree<T>::INORDER2(Node<T>* n)//RNL
{
	if (n != nullptr)// this check is the base case of this recursive function it will terminate if the sent node is a nullptr;
	{
		// now you know that the node has something to its left or right;
		//For Inorder, you traverse from the left subtree to the root then to the right subtree.
		INORDER2(n->right);
		cout << n->data;
		cout << "->(" << n->colour << ") ";
		INORDER2(n->left);
	}
}
template<class T>
void RBTree<T>::PREORDER2(Node<T>* n)//NRL
{
	if (n != nullptr)// this check is the base case of this recursive function it will terminate if the sent node is a nullptr;
	{
		// now you know that the node has something to its left or right;
		//For Preorder, you traverse from the root to the left subtree then to the right subtree.
		cout << n->data;
		cout << "->(" << n->colour << ") ";
		PREORDER2(n->right);
		PREORDER2(n->left);
	}
}
template<class T>
void RBTree<T>::POSTORDER2(Node<T>* n)//RLN
{
	if (n != nullptr)// this check is the base case of this recursive function it will terminate if the sent node is a nullptr;
	{
		// now you know that the node has something to its left or right;
		//For Post order, you traverse from the left subtree to the right subtree then to the root.
		POSTORDER2(n->right);
		POSTORDER2(n->left);
		cout << n->data;
		cout << "->(" << n->colour << ") ";
	}
}
//           END OF WRAPPER FUNCTIONS
//Red Black Tree functions
template<class T>
void RBTree<T>::insert(T value)
{
	/*Node<T>* BSTpointer = */
	insertBST(this->root, value);
	/*if (BSTpointer == nullptr)
	{
		
	}
	else
	{
		return;
	}*/
	//else
	//{
	//	//Node<T>* uncle;
	//	//fixRBTree(BSTpointer,uncle);
	//}
}
template<class T>
void RBTree<T>::SearchByValue(T value)
{
	if (this->root != nullptr)
	{
		Node<T>* temp = Search_node(this->root, value);
		if (temp != nullptr)
		{
			if (value == temp->data)
			{
				cout << "Value found: ";
				cout << temp->data;
				cout << "->(" << temp->colour << ") ";
				cout << endl;
			}
		}
		else
		{
			cout << "Value not found...:(" << endl;
		}
	}
	else
	{
		cout << "Tree is empty...!" << endl;
	}

}
template<class T>
void RBTree<T>::DestroyallTree()
{
	if (this->root != nullptr)
	{
		destroy(this->root);
	}
	else
	{
		cout << "Tree is empty...!" << endl;
	}
}
template<class T>
void RBTree<T>::FindParent(T value)
{
	if (this->root != nullptr)
	{
		getParent(this->root, value);
	}
	else
	{
		cout << "Tree is empty...!" << endl;
	}
}
template<class T>
void RBTree<T>::inorder1()
{
	if (this->root != nullptr)
	{
		INORDER1(this->root);
	}
	else
		cout << "Tree is empty...!" << endl;
}

template<class T>
void RBTree<T>::preorder1()
{
	if (this->root != nullptr)
	{
		PREORDER1(this->root);
	}
	else
	{
		cout << "Tree is empty...!" << endl;
	}
}

template<class T>
void RBTree<T>::postorder1()
{
	if (this->root != nullptr)
	{
		POSTORDER1(this->root);
	}
	else
		cout << "Tree is empty...!" << endl;
}

template<class T>
void RBTree<T>::inorder2()
{
	if (this->root != nullptr)
	{
		INORDER2(this->roo.t);
	}
	else
		cout << "Tree is empty...!" << endl;
}

template<class T>
void RBTree<T>::preorder2()
{
	if (this->root != nullptr)
	{
		PREORDER2(this->root);
	}
	else
		cout << "Tree is empty...!" << endl;
}

template<class T>
void RBTree<T>::postorder2()
{
	if (this->root != nullptr)
	{
		POSTORDER2(this->root);
	}
	else
		cout << "Tree is empty...:(" << endl;
}

