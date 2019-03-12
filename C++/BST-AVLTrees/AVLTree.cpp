/******************************************************************************/
/*!
\file   AVLTree.cpp
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS280
\par    Assignment #4
\date   3/26/2017
*/
/******************************************************************************/
#include "ObjectAllocator.h"
#include <stack>

/******************************************************************************/
/*!
	\brief
		AVL Constructor

	\param OA
		ObjectAllocator pointer

	\param ShareOA
		Bool if object will be shared
*/
/******************************************************************************/
template<typename T>
AVLTree<T>::AVLTree(ObjectAllocator *OA, bool ShareOA) : BSTree<T>::BSTree(OA, ShareOA) { }

/******************************************************************************/
/*!
	\brief
		Destructor
*/
/******************************************************************************/
template<typename T>
AVLTree<T>::~AVLTree() { BSTree<T>::clear(); }

/******************************************************************************/
/*!
	\brief
		If balance factor is implemented

	\return
		If balance factor is implemented
*/
/******************************************************************************/
template<typename T>
bool AVLTree<T>::ImplementedBalanceFactor() { return false; }

/******************************************************************************/
/*!
	\brief
		Inserts a value into a tree

	\param
		Value to insert
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::insert(const T& value) { RecursiveInsert(value); }

/******************************************************************************/
/*!
	\brief
		Removes a value from the tree

	\param value
		Value to be removed
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::remove(const T& value) 
{ 
	RecursiveDelete(value);
}

/******************************************************************************/
/*!
	\brief
		Recursive function to delete an item

	\param value
		Value to be removed
*/
/******************************************************************************/
template <typename T>
void AVLTree<T>::RecursiveDelete(const T& value)
{
	std::stack<typename BSTree<T>::BinTree*> nodes;  // Creates a stack of nodes
	Delete(BSTree<T>::root_, value, nodes); // Calls the insert function that will also balance the tree
	AVLTraverseCounter(BSTree<T>::root_);     // Recalculates all of the counts
}

/******************************************************************************/
/*!
	\brief
		Delete function that pushes the tree onto a stack so that the tree can
		be balanced after items have been removed

	\param tree
		Tree to be removed from

	\param Data
		Data to be searched for to delete

	\param delNotes
		Stack to store the tree
*/
/******************************************************************************/
template <typename T>
void AVLTree<T>::Delete(typename BSTree<T>::BinTree &tree, T Data, std::stack<typename BSTree<T>::BinTree*>& delNodes)
{
	if (tree == 0)                                   // Return if tree is empty
	{
		BalanceAVLTree(delNodes);                    // Balance first
		return;
	}
	else if (Data < tree->data)                      // If data is in the left subtree
	{
		delNodes.push(&tree);                        // Push node on the stack
		Delete(tree->left, Data, delNodes);          // Go left
	}

	else if (Data > tree->data)
	{
		delNodes.push(&tree);
		Delete(tree->right, Data, delNodes);
	}

	else                                             // If data is found
	{
		if (tree->left == 0)                         // If you're at the end of the left subtree
		{
			typename BSTree<T>::BinTree temp = tree;
			tree = tree->right;
			BSTree<T>::free_node(temp);
			BalanceAVLTree(delNodes);
		}
		else if (tree->right == 0)                   // If you're at the end of the right subtree
		{
			typename BSTree<T>::BinTree temp = tree;
			tree = tree->left;
			BSTree<T>::free_node(temp);
			BalanceAVLTree(delNodes);
		}
		else
		{
			typename BSTree<T>::BinTree pred = 0;
			BSTree<T>::find_predecessor(tree, pred);
			tree->data = pred->data;
			delNodes.push(&tree);
			Delete(tree->left, tree->data, delNodes);
		}
	}
}

/******************************************************************************/
/*!
	\brief
		Recursive function that is called in insert to first create a stack
		and then to call a third insert functino that will be used to balance
		the tree

	\param value
		Value that will be inserted
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::RecursiveInsert(const T& value)
{
	std::stack<typename BSTree<T>::BinTree*> nodes;  // Creates a stack of nodes
	// Calls the insert function that will also balance the tree
	InsertAVLItem2(BSTree<T>::root_, value, nodes);  
	AVLTraverseCounter(BSTree<T>::root_);     // Recalculates all of the counts
}

/******************************************************************************/
/*!
	\brief
		Inserts items into the tree by pushing them on the stack and calling
		balance, to keep the tree balanced after insertnig one

	\param tree
		Tree to be inserted into

	\param Data
		Data to be inserted

	\param nodes
		Stack where the nodes are stored
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::InsertAVLItem2(typename BSTree<T>::BinTree& tree, T Data, 
	std::stack<typename BSTree<T>::BinTree*> & nodes)
{
	if (tree == 0)
	{
		tree = BSTree<T>::make_node(Data);
		BalanceAVLTree(nodes); // Balance it now
	}
	else if (Data < tree->data)
	{
		nodes.push(&tree); // save visited node
		InsertAVLItem2(tree->left, Data, nodes);
	}
	else if (Data > tree->data)
	{
		nodes.push(&tree); // save visited node
		InsertAVLItem2(tree->right, Data, nodes);
	}
} 

/******************************************************************************/
/*!
	\brief
		Function that traverses the tree to reset the counters for each node
		after all of tree has been balanced and some of the nodes rotated
		because after that, some of the nodes won't have the correct count
		since they were not switched when they were rotated

	\param tree
		Tree that is being traversed
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::AVLTraverseCounter(typename BSTree<T>::BinTree tree)
{
	if (tree == 0)
		return;
	tree->count = SubTreeCount(tree);  // Uses helper function to calculate count of current subtree
	AVLTraverseCounter(tree->left);    // Traverses through the tree
	AVLTraverseCounter(tree->right);
}

/******************************************************************************/
/*!
	\brief
		Rotates the tree right once

	\param tree
		Tree to rotate
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::RotateRight(typename BSTree<T>::BinTree& tree)
{
	typename BSTree<T>::BinTree temp = tree;   // Rotates right and switches nodes around
	tree = tree->left;         
	temp->left = tree->right;
	tree->right = temp;
}

/******************************************************************************/
/*!
	\brief
		Rotates the tree left once

	\param tree
		Tree to rotate
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::RotateLeft(typename BSTree<T>::BinTree& tree)
{
	typename BSTree<T>::BinTree temp = tree;   // Rotates left and switches nodes around
	tree = tree->right;
	temp->right = tree->left;
	tree->left = temp;
}

/******************************************************************************/
/*!
	\brief
		Balances the AVL tree

	\param nodes
		A stack of the nodes in the tree
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::BalanceAVLTree(std::stack<typename BSTree<T>::BinTree*> & nodes)
{
	while (!nodes.empty())
	{
		// Looking at the current node on the top of the stack
		typename BSTree<T>::BinTree* tree = nodes.top();
		int rightHeight = BSTree<T>::tree_height((*tree)->right);
		int leftHeight = BSTree<T>::tree_height((*tree)->left);
		typename BSTree<T>::BinTree *R, *RL, *RR, *L, *LR, *LL;

		// If the tree needs to be balanced
		if (rightHeight - 1 > leftHeight || leftHeight - 1 > rightHeight)
		{
			if (rightHeight > leftHeight)  // If the right side of the tree is longer than the left
			{
				// Delcaring pointers to the right, right left, and right right nodes of the tree
				R = &(*tree)->right;
				RL = &(*tree)->right->left;
				RR = &(*tree)->right->right;
				int RLHeight = BSTree<T>::tree_height(*RL);
				int RRHeight = BSTree<T>::tree_height(*RR);
				// If the right left is greater than the right right height
				if (RLHeight > RRHeight)
				{
					RotateRight(*R);   // Rotate the right node right
					RotateLeft(*tree); // Rotate the top of the tree left
				}

				else                    // If the right left is less or they are equal
					RotateLeft(*tree);  // Rotate the top of the tree left
			}

			else if (rightHeight < leftHeight) // If the right side of the tree is smaller than the left
			{
				// Declaring pointers to the left, left right, and left left nodes of the tree
				L = &(*tree)->left;
				LR = &(*tree)->left->right;
				LL = &(*tree)->left->left;
				int LLHeight = BSTree<T>::tree_height(*LL);
				int LRHeight = BSTree<T>::tree_height(*LR);
				// If the left left is less than the left right height
				if (LLHeight < LRHeight)
				{
					RotateLeft(*L);       // Rotates the left node left
					RotateRight(*tree);   // Rotate the top of the tree right
				}
				else                      // If the left left is greater or equal to the left right
					RotateRight(*tree);   // Rotate the top of the tree right
			}
		}
		nodes.pop();  // Take that node off the top of the stack for next time
	}
}

/******************************************************************************/
/*!
	\brief
		Chops nodes off the tree

	\param tree
		Tree to chop
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::chop(typename BSTree<T>::BinTree tree)
{
	if (!tree)            // If there is nothing in the tree, return
		return;
	chop(tree->left);     // Chop the left side of the tree
	chop(tree->right);    // Chop the right side of the tree
	BSTree<T>::allocate->Free(tree);  // Deallocate the tree
}

/******************************************************************************/
/*!
	\brief
		Copies data to the tree

	\param tree
		Tree to be copied
*/
/******************************************************************************/
template<typename T>
void AVLTree<T>::copy(typename BSTree<T>::BinTree tree)
{
	if (!tree)              // If there is nothing in the tree, return
		return;
	BSTree<T>::insert(tree->data); // Insert the data into the tree
	copy(tree->left);              // Copy over new data into left tree
	copy(tree->right);			   // Copy over new data into right tree
}

/******************************************************************************/
/*!
	\brief
		Counts the nodes in a subtree

	\param tree
		Tree to be counted

	\return
		Returns the count
*/
/******************************************************************************/
template<typename T>
int AVLTree<T>::SubTreeCount(typename BSTree<T>::BinTree tree) const
{
	if (tree == 0)  // If there is nothing in the tree, return
		return 0;
	
    //Add count of left and right trees, add 1 for current node
	return SubTreeCount(tree->left) + SubTreeCount(tree->right) + 1;
}
