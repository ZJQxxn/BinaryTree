//Iterators.h : Implementation of several kind of iterators for a binary tree.
#ifndef TREE_ITER
#define TREE_ITER
#include "BinaryTree.h"
#include "TreeNode.h"
#include <stack>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

//base abstract class for all traverse iterators
template<typename T>
class BasicIterator
{
public:
	virtual const T& operator*() = 0;
	virtual bool next() = 0;
};


/////////////////////////////////////////////////////////////////////////
//class:'PreorderIterator' for traverse a tree in preorder
template <typename T>
class PreOrderIterator:public BasicIterator<T> 
{
private:
	TreeNode<T>* currentPtr;
	stack<TreeNode<T>*> nodes;

	void _preparation();
public:
	PreOrderIterator(BinaryTree<T>& tree);
	const T& operator * ();
	bool next();
};


//constructor
template<typename T>
PreOrderIterator<T>::PreOrderIterator(BinaryTree<T>& tree)
	:BasicIterator<T>()
{
	currentPtr = tree.root;
	nodes.push(currentPtr);
}


//operations
/*
	Get value of iterator.
*/
template<typename T>
const T& PreOrderIterator<T>::operator * ()
{
	return this->currentPtr->data;
}

/*
	Get next node based on preorder traverse.
*/
template <typename T>
bool PreOrderIterator<T>::next()
{
	if (nodes.empty())
	{
		return false;
	}
	currentPtr = nodes.top();
	nodes.pop();
	if (currentPtr->rightChild != nullptr)
	{
		nodes.push(currentPtr->rightChild);
	}
	if (currentPtr->leftChild != nullptr)
	{
		nodes.push(currentPtr->leftChild);
	}
	return true;
}



/////////////////////////////////////////////////////////////////////////
//class:'InOrderIterator' for traverse a binary tree in inorder
template<typename T>
class InOrderIterator:public BasicIterator<T>
{
private:
	TreeNode<T>* currentPtr;
	TreeNode<T>* tempPtr;
	stack<TreeNode<T>*>	nodes;
	
public:
	InOrderIterator(BinaryTree<T>&);
	const T& operator *();
	bool next();
};


//constructor
template<typename T>
InOrderIterator<T>::InOrderIterator(BinaryTree<T>& tree)
	:BasicIterator<T>()
{
	this->currentPtr = tree.root;
	this->tempPtr = tree.root;
}


//operations
/*
	Get value of the iterator.
*/
template<typename T>
const T& InOrderIterator<T>::operator *()
{
	return this->currentPtr->data;
}

/*
	Move iterator to next node based on inorder traverse.
*/
template<typename T>
bool InOrderIterator<T>::next()
{
	currentPtr = tempPtr;
	while (currentPtr)
	{
		nodes.push(currentPtr);
		currentPtr = currentPtr->leftChild;
	}
	if (nodes.empty())
	{
		return false;
	}
	else
	{
		currentPtr = nodes.top();
		nodes.pop();
		tempPtr = currentPtr->rightChild;
		return true;
	}
}



/////////////////////////////////////////////////////////////////////////
//class for traverse tree in postorder
template<typename T>
class PostOrderIterator:public BasicIterator<T>
{
private:
	TreeNode<T>* currentPtr;
	vector<TreeNode<T>*> traversed;
	stack<TreeNode<T>*>	nodes;

public:
	PostOrderIterator(BinaryTree<T>&);
	const T& operator *();
	bool next();
};

//constructor
template <typename T>
PostOrderIterator<T>::PostOrderIterator(BinaryTree<T>& tree)
	:BasicIterator<T>()
{
	currentPtr = tree.root;
	traversed.push_back(currentPtr);
	nodes.push(currentPtr);
}


//operations
template <typename T>
const T& PostOrderIterator<T>::operator *()
{
	return currentPtr->data;
}

template <typename T>
bool PostOrderIterator<T>::next()
{
	while (currentPtr->leftChild || currentPtr->rightChild)
	{
		if (currentPtr->rightChild && 
			find(traversed.begin(), traversed.end(), currentPtr->rightChild) == traversed.end())
		{
			traversed.push_back(currentPtr->rightChild);
			nodes.push(currentPtr->rightChild);
		}
		if (currentPtr->leftChild && 
			find(traversed.begin(), traversed.end(), currentPtr->leftChild) == traversed.end())
		{
			traversed.push_back(currentPtr->leftChild);
			nodes.push(currentPtr->leftChild);
		}
		if (nodes.empty())
		{
			return false;
		}
		currentPtr = nodes.top();
	}
	currentPtr = nodes.top();
	nodes.pop();
	return true;
}



/////////////////////////////////////////////////////////////////////////
//class for traverse tree in levelorder
template<typename T>
class LevelOrderIterator:public BasicIterator<T>
{
private:
	TreeNode<T>* currentPtr;
	queue<TreeNode<T>*>	nodes;
	vector<TreeNode<T>*> traversed;
public:
	LevelOrderIterator(BinaryTree<T>&);
	const T& operator *();
	bool next();
};


//constructor
template <typename T>
LevelOrderIterator<T>::LevelOrderIterator(BinaryTree<T>& tree)
	:BasicIterator<T>()
{
	currentPtr = tree.root;
	traversed.push_back(currentPtr);
	nodes.push(currentPtr);
}


//operations
template <typename T>
const T& LevelOrderIterator<T>::operator*()
{
	return currentPtr->data;
}

template <typename T>
bool LevelOrderIterator<T>::next()
{
	while (currentPtr->leftChild || currentPtr->rightChild)
	{
		if (currentPtr->leftChild &&
			find(traversed.begin(), traversed.end(), currentPtr->leftChild) == traversed.end())
		{
			nodes.push(currentPtr->leftChild);
			traversed.push_back(currentPtr->leftChild);
		}
		if (currentPtr->rightChild &&
			find(traversed.begin(), traversed.end(), currentPtr->rightChild) == traversed.end())
		{
			nodes.push(currentPtr->rightChild);
			traversed.push_back(currentPtr->rightChild);
		}
		currentPtr = nodes.back();
	}
	if (nodes.empty())
	{
		return false;
	}
	currentPtr = nodes.front();
	nodes.pop();
	return true;
}
#endif