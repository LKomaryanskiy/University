/*!
* file: TreeNode.h
* written: 1/06/2016
* autor: L.Komaryanskiy
* description: template class
* Tree Node
*/
#pragma once
#include <iostream>

template<class T>
struct TreeNode
{
	T value;
	TreeNode* left;
	TreeNode* right;
	TreeNode(const T& val) 
		: value(val) {};
	~TreeNode() {};
	void Print() { std::cout << value };
};