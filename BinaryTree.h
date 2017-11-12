//BinartTree.h : Decalretion and implementation of template binary class.
#ifndef BINARYTREE_H
#define BINARYTREE_H
#include "TreeNode.h"
#include <queue>
using std::queue;

//predefine some iterator class
template <typename T>
class BasicIterator;

template <typename T>
class PreOrderIterator;

template <typename T>
class InOrderIterator;

template<typename T>
class PostOrderIterator;

template<typename T>
class LevelOrderIterator;


//////////////////////////////////////////////////////////////////////
//template class:'BinaryTree'
template <typename T>
class BinaryTree
{
	//friend class BasicIterator<T>;
	friend class PreOrderIterator<T>;
	friend class InOrderIterator<T>;
	friend class PostOrderIterator<T>;
	friend class LevelOrderIterator<T>;

private:
	TreeNode<T>* root;
	
	//private operations
	TreeNode<T>* _copy(TreeNode<T>*);
	void _delete(TreeNode<T>*);
	TreeNode<T>* _find(TreeNode<T>*,const T& value);
	void _preTraverse(TreeNode<T>*);
	void _inTraverse(TreeNode<T>*);
	void _postTraverse(TreeNode<T>*);
public:
	//constructor and destructor
	BinaryTree();
	BinaryTree(const T& rootValue);
	BinaryTree(BinaryTree<T>&, BinaryTree<T>&, const T&);
	BinaryTree(const BinaryTree<T>&);
	~BinaryTree();

	//operations
	const T& getRoot();
	void addNode(const T& fatherValue,const T& value,bool left=true);
	bool isEmpty();
	int countLeaves();
	void clearAll();
	BinaryTree& leftSubTree();
	BinaryTree& rightSubTree();
	void preTraverse();
	void inTraverse();
	void postTraverse();
	void levelTraverse();
};


////////////////////////////////////////////////////////////////////
//constructor and destructor
template <typename T>
BinaryTree<T>::BinaryTree()
{
	root = nullptr;
}

template <typename T>
BinaryTree<T>::BinaryTree(const T& rootValue)
{
	root = new TreeNode<T>(rootValue);
}

template <typename T>
BinaryTree<T>::BinaryTree(BinaryTree<T>& left, BinaryTree<T>& right, const T& rootValue)
{
	root = new TreeNode<T>(rootValue);
	root->leftChild = _copy(left.root);
	root->rightChild = _copy(right.root);
}

template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)
{
	root = _copy(tree.root);
}

template <typename T>
BinaryTree<T>::~BinaryTree()
{
	if (!isEmpty())
	{
		clearAll();
	}
}


////////////////////////////////////////////////////////////////////
//private operations
/*
	Get root value.
*/
template <typename T>
const T& BinaryTree<T>::getRoot()
{
	return root->data;
}

/*
	Find a node and return its pointer.
*/
template<typename T>
TreeNode<T>* BinaryTree<T>::_find(TreeNode<T>* beginPos, const T& value)
{
	if (beginPos->data == value)
	{
		return beginPos;
	}
	else
	{
		TreeNode<T>* ptr = nullptr;
		if ((ptr = _find(beginPos->leftChild, value)) != nullptr)
		{
			return ptr;
		}
		else if ((ptr = _find(beginPos->rightChild, value)) != nullptr)
		{
			return ptr;
		}
		else
		{
			return nullptr;
		}
	}
}

/*
	Copy a node.
*/
template<typename T>
TreeNode<T>* BinaryTree<T>::_copy(TreeNode<T>* beginPos)
{
	if (!beginPos)
	{
		return nullptr;
	}
	else
	{
		return new TreeNode<T>(beginPos->data, _copy(beginPos->leftChild), _copy(beginPos->rightChild));
	}

}

/*
	Delete a node given its pointer.
*/
template<typename T>
void BinaryTree<T>::_delete(TreeNode<T>* ptr)
{
	if (ptr->leftChild)
	{
		_delete(ptr->leftChild);
	}
	if (ptr->rightChild)
	{
		_delete(ptr->rightChild);
	}
	delete ptr;
}

/*
	Reursively traverse in inorder.
*/
template<typename T>
void BinaryTree<T>::_inTraverse(TreeNode<T>* current)
{
	if (current)
	{
		_inTraverse(current->leftChild);
		cout << current->data << "  ";
		_inTraverse(current->rightChild);
	}
}

/*
	Reursively traverse in preorder.
*/
template<typename T>
void BinaryTree<T>::_preTraverse(TreeNode<T>* current)
{
	if (current)
	{
		cout << current->data << "  ";
		_inTraverse(current->leftChild);
		_inTraverse(current->rightChild);
	}
}

/*
	Reursively traverse in postorder.
*/
template<typename T>
void BinaryTree<T>::_postTraverse(TreeNode<T>* current)
{
	if (current)
	{
		_inTraverse(current->leftChild);
		_inTraverse(current->rightChild);
		cout << current->data << "  ";
	}
}


///////////////////////////////////////////////////////////////
//public operations
/*
	Determin whether tree is empty.
*/
template<typename T>
bool BinaryTree<T>::isEmpty()
{
	return root == nullptr;
}

/*
	Add a node in binary tree given its father node's value 
	and a boolean determin add as left child or right child.
*/
template<typename T>
void BinaryTree<T>::addNode(const T& fatherValue, const T& value, bool left = true)
{
	TreeNode<T>* newNode = new TreeNode<T>(value);
	TreeNode<T>* father = _find(root, fatherValue);
	if (father)
	{
		if (left)
		{
			father->leftChild = newNode;
		}
		else
		{
			father->rightChild = newNode;
		}
	}
	else
	{
		cout << "Can't find the father node\n";
	}
}

/*
	Count the number of leaves of this tree.
*/
template<typename T>
int BinaryTree<T>::countLeaves()
{
	queue<TreeNode<T>*> nodes;
	TreeNode<T>* current = root;
	int count = 0;
	//traverse in level order
	while (root->leftChild || root->rightChild)
	{
		if (current->leftChild)
		{
			nodes.push(current->leftChild);
		}
		if (current->rightChild)
		{
			nodes.push(current->rightChild);
		}
		current = nodes.front();
		nodes.pop();
		//find a leaf node
		if (!current->leftChild && !current->rightChild)
		{
			count++;
		}
		//finish traverse all the nodes
		if (nodes.empty())
		{
			break;
		}
	}

	//if tree just has a root,then the root is also a leaf node.
	return count ? count : 1;
}

/*
	Clear all nodes in tree.
*/
template<typename T>
void BinaryTree<T>::clearAll()
{
	_delete(root);
	root = nullptr;
}

/*
	Get left subtree.
*/
template<typename T>
BinaryTree<T>& BinaryTree<T>::leftSubTree()
{
	BinaryTree<T>* tree = new BinaryTree<T>();
	tree->root = _copy(this->root->leftChild);
	return *tree;
}

/*
	Get right subtree.
*/
template<typename T>
BinaryTree<T>& BinaryTree<T>::rightSubTree()
{
	BinaryTree<T>* tree = new BinaryTree<T>();
	tree->root = _copy(this->root->rightChild);
	return *tree;
}

/*
	Traverse tree in preorder.
*/
template<typename T>
void BinaryTree<T>::preTraverse()
{
	_preTraverse(root);
	cout << endl;
}

/*
	Traverse tree in inorder.
*/
template<typename T>
void BinaryTree<T>::inTraverse()
{
	_inTraverse(root);
	cout << endl;
}

/*
	Traverse tree in postorder.
*/
template<typename T>
void BinaryTree<T>::postTraverse()
{
	_postTraverse(root);
	cout << endl;
}

/*
	Traverse tree in levelorder.
*/
template<typename T>
void BinaryTree<T>::levelTraverse()
{
	queue<TreeNode<T>*> nodes;
	TreeNode<T>* current = root;
	while (current)
	{
		cout << current->data << "  ";
		if (current->leftChild)
		{
			nodes.push(current->leftChild);
		}
		if (current->rightChild)
		{
			nodes.push(current->rightChild);
		}
		if (nodes.empty())
		{
			cout << endl;
			return;
		}
		current = nodes.front();
		nodes.pop();
	}
}

#endif
