//main.cpp : Main function to test binary tree.
#include "BinaryTree.h"
#include "Iterators.h"
#include <iostream>
#include <cstdlib>
using namespace std;


/*
	Test traverse by using iterators
*/
template <typename T>
void testIterator(BinaryTree<T>& tree)
{
	cout << "\n=========Traverse using iterator===============\n";
	BasicIterator<int>* iterator = new LevelOrderIterator<int>(tree);
	cout << "Level order traverse : ";
	while (iterator->next())
	{
		cout << *(*iterator) << "  ";
	}
	cout << endl;

	iterator = new PreOrderIterator<int>(tree);
	cout << "Preorder traverse : ";
	while (iterator->next())
	{
		cout << *(*iterator) << "  ";
	}
	cout << endl;

	iterator = new InOrderIterator<int>(tree);
	cout << "Inorder traverse : ";
	while (iterator->next())
	{
		cout << *(*iterator) << "  ";
	}
	cout << endl;

	iterator = new PostOrderIterator<int>(tree);
	cout << "Postorder traverse : ";
	while (iterator->next())
	{
		cout << *(*iterator) << "  ";
	}
	cout << endl;
}

/*
	Test traverse by using recurssion.
*/	
template <typename T>
void testRecurssion(BinaryTree<T>& tree)
{
	cout << "\n=========Traverse using recurssion===============\n";
	cout << "Inorder traverse : ";
	tree.inTraverse();
	cout << "Preorder traverse : ";
	tree.preTraverse();
	cout << "Postorder traverse : ";
	tree.postTraverse();
	cout << "Level order traverse : ";
	tree.levelTraverse();
}


int main()
{
	//Add terms into tree.
	BinaryTree<int> tree(1);
	tree.addNode(1,2,true);
	tree.addNode(1,3,false);
	tree.addNode(2, 4, true);
	tree.addNode(2, 5, false);
	tree.addNode(4, 6, false);

	//test traverse
	testIterator(tree);
	testRecurssion(tree);

	//get subtrees
	cout << "\n=========Get subtree===============\n";
	cout << "Levelorder of leftsubtree : ";
	tree.leftSubTree().levelTraverse();
	cout << "Levelorder of rightsubtree : ";
	tree.rightSubTree().levelTraverse();

	//other operations
	cout << "\n=========Other operations===============\n";
	cout << "The number of leaf nodes :" << tree.countLeaves() << endl;
	cout << "Before clear tree is empty ? " << boolalpha << tree.isEmpty() << endl;
	tree.clearAll();
	cout << "Ater clear all nodes ,is tree empty ? " << boolalpha << tree.isEmpty() << endl;
	
	//Test other constructors
	cout << "\n=========Other constructors===============\n";
	BinaryTree<int> tree2(10);
	BinaryTree<int> tree3(tree2);
	BinaryTree<int> tree4(tree2, tree3, 12);
	tree4.levelTraverse();
	cout << "Root value : " << tree4.getRoot() << endl;
	system("pause");
	return 0;
}