/*!
* file: BinTree.h
* written: 1/06/2016
* autor: L.Komaryanskiy
* description: declaration 
* template class binary search tree
*/
#pragma once
#include "TreeNode.h"

template<class T>
class BinTree
{
public:
	BinTree() : _root (nullptr) {};
	~BinTree();

	void AddItem(const T& item);
	bool FindAndDeleteItem(const T& item);
	bool FindItem(const T& item);

	void Print();
private:
	bool RecursiveFind(const T& item, TreeNode<T>* node);
	TreeNode<T>* RecursiveDelete(const T& item, TreeNode<T>* node);
	void RecursiveDeleteAll(TreeNode<T>* node);
	void RecursivePrint(TreeNode<T>* node);
	TreeNode<T>* RecursiveAdd(const T& item, TreeNode<T>* node);
	TreeNode<T>* _root;
};



template<class T>
BinTree<T>::~BinTree()
{
	RecursiveDeleteAll(_root);
};

template<class T>
void BinTree<T>::AddItem(const T & item)
{
	if (_root == nullptr)
	{
		_root = RecursiveAdd(item, _root);
		return;
	}
	RecursiveAdd(item, _root);
};

template<class T>
bool BinTree<T>::FindAndDeleteItem(const T & item)
{
	if (FindItem(item))
	{
		RecursiveDelete(item, _root);
		return true;
	}
	return false;
};

template<class T>
bool BinTree<T>::FindItem(const T & item)
{
	return RecursiveFind(item, _root);
};

template<class T>
void BinTree<T>::Print()
{
	RecursivePrint(_root);
};

template<class T>
bool BinTree<T>::RecursiveFind(const T& item, TreeNode<T>* node)
{
	if (node == nullptr)
	{
		return false;
	}
	if (node->value == item)
	{
		return true;
	}
	if (item < node->value) {
		return RecursiveFind(item, node->left);
	}
	if (item > node->value) {
		return RecursiveFind(item, node->right);
	}
};

template<class T>
TreeNode<T>* BinTree<T>::RecursiveDelete(const T & item, TreeNode<T>* node)
{
	TreeNode<T>* ptr_tmp_1, *ptr_tmp_2;
	if (item < node->value)
	{
		node->left = RecursiveDelete(item, node->left);
	}
	else if (item > node->value)
	{
		node->right = RecursiveDelete(item, node->right);
	}
	else
	{
		ptr_tmp_2 = node;
		if (node->right == nullptr)
		{
			node = node->left;
		}
		else if (node->left == nullptr)
		{
			node = node->right;
		}
		else
		{
			ptr_tmp_1 = node->left;
			if (ptr_tmp_1->right)
			{
				while (ptr_tmp_1->right->right != nullptr)
				{
					ptr_tmp_1 = ptr_tmp_1->right;
				}
				node->value = ptr_tmp_1->right->value;
				ptr_tmp_2 = ptr_tmp_1->right;
				ptr_tmp_1->right = ptr_tmp_1->right->left;
			}
			else
			{
				node->value = ptr_tmp_1->value;
				ptr_tmp_2 = ptr_tmp_1;
				node->left = node->left->left;
			}
		}
		delete ptr_tmp_2;
	}
	return node;
};

template<class T>
void BinTree<T>::RecursiveDeleteAll(TreeNode<T> * node)
{
	if (node != nullptr)
	{
		RecursiveDeleteAll(node->left);
		RecursiveDeleteAll(node->right);
		delete node;
	}
};

template<class T>
void BinTree<T>::RecursivePrint(TreeNode<T> * node)
{
	if (node != nullptr)
	{
		RecursivePrint(node->left);
		cout << node->value << endl << endl;
		RecursivePrint(node->right);
	}
};

template<class T>
TreeNode<T>* BinTree<T>::RecursiveAdd(const T & item, TreeNode<T>* node)
{
	if (node == nullptr)
	{
		node = new TreeNode<T>(item);
		node->left = nullptr;
		node->right = nullptr;
	}
	else if (item < node->value) 
	{
		node->left = RecursiveAdd(item, node->left);
	}
	else
	{
		node->right = RecursiveAdd(item, node->right);
	}
	return node;
};


