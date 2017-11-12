//TreeNode.h : Declaretion and implementation of the node of binary tree.
#ifndef TREENODE_H
#define TREENODE_H
 

//template class:'TreeNode'
template <typename T>
class TreeNode
{
public:
	T data;
	TreeNode<T>* leftChild;
	TreeNode<T>* rightChild;

	TreeNode(T data,TreeNode<T>* left=nullptr,TreeNode<T>* right=nullptr)
		: data(data)
		, leftChild(left)
		, rightChild(right)
	{
	}
};

#endif