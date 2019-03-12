/******************************************************************************/
/*!
\file   BSTree.cpp
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS280
\par    Assignment #4
\date   3/26/2017
*/
/******************************************************************************/
#include "ObjectAllocator.h"
#include <iostream>

/******************************************************************************/
/*!
	\brief
		BST Constructor

	\param OA
		ObjectAllocator pointer

	\param ShareOA
		Bool if object will be shared
*/
/******************************************************************************/
template<typename T>
BSTree<T>::BSTree(ObjectAllocator *OA, bool ShareOA) : allocate(OA), created(false), 
					ifShare(ShareOA), root_(NULL)
{
	if (OA == 0)                 // If the Object Allocator doesn't already exist
	{
		OAConfig con(true);      // Create a new object allocator because one doesn't already exist
		allocate = new ObjectAllocator(sizeof(BinTreeNode), con);
		created = true;          // We created our own objectAllocator
	}

	else if (OA != 0)            // If the ObjectAllocator already exists, set the pointer to it
	{
		allocate = OA;
		created = false;         // We didn't create our own objectAllocator
	}
}

/******************************************************************************/
/*!
	\brief
		Copy constructor

	\param rhs
		Object to be copied
*/
/******************************************************************************/
template<typename T>
BSTree<T>::BSTree(const BSTree& rhs) : allocate(rhs.allocate), created(rhs.created), 
										ifShare(rhs.ifShare), root_(NULL)
{
	if (ifShare == false)     // If we're not sharing an allocator
	{
		OAConfig con(true);   // Create a new object allocator
		allocate = new ObjectAllocator(sizeof(BinTreeNode), con);
		created = true;
	}

	copy(rhs.root_);           // Copy rhs into the this root
	TraverseCounter(root_, rhs.root_);  // Copy the rhs count into the this count
}

/******************************************************************************/
/*!
	\brief
		Assignment operator

	\param rhs
		Object to be assigned

	\return
		Returns new object that was assigned
*/
/******************************************************************************/
template<typename T>
typename BSTree<T>::BSTree& BSTree<T>::operator=(const BSTree& rhs)
{
	clear();
	copy(rhs.root_);
	return *this;
}

/******************************************************************************/
/*!
	\brief
		Inserts value into the tree

	\param value
		Value to insert
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::insert(const T& value)
{
	InsertItem(root_, value);
}

/******************************************************************************/
/*!
	\brief
		Finds a value in the tree

	\param value
		Value to be found

	\param compares
		Number of comparisons made before value was found

	\return
		Returns if the value was found
*/
/******************************************************************************/
template<typename T>
bool BSTree<T>::find(const T& value, unsigned &compares) const
{
	BinTree temp = root_;
	return ItemExists(temp, value, compares);
}

/******************************************************************************/
/*!
	\brief
		Determines if the tree is empty

	\return
		Returns if the tree is empty or not
*/
/******************************************************************************/
template<typename T>
bool BSTree<T>::empty(void) const
{
	if (root_ == NULL)
		return true;
	return false;
}

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////Root Functions////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Makes a new node in the tree

	\param value
		Value to be stored in the new node

	\return
		Returns a pointer to the new node
*/
/******************************************************************************/
template<typename T>
typename BSTree<T>::BinTree BSTree<T>::make_node(const T& value)
{
	BinTree node;
	try
	{
		// Allocate memory for the object.
		BinTree mem = reinterpret_cast<BinTree>(allocate->Allocate());
		node = new (mem) BinTreeNode(value); // Construct the object in the memory.
	}
	catch (const OAException &e)
	{
		throw(BSTException(BSTException::E_NO_MEMORY, e.what()));
	}

	node->data = value;			// Set the value to the data of the new node
	node->right = 0;		    // Set right and left of node to 0
	node->left = 0;
	(node->count)++;		    // Increment the count of the new node
	return node;
}

/******************************************************************************/
/*!
	\brief
		Returns the root

	\return
		The root
*/
/******************************************************************************/
template<typename T>
typename BSTree<T>::BinTree BSTree<T>::root(void) const { return root_; }

/******************************************************************************/
/*!
	\brief
		Returns a reference to the root

	\return
		Reference to the root
*/
/******************************************************************************/
template<typename T>
typename BSTree<T>::BinTree& BSTree<T>::get_root(void)
{
	BinTree& refRoot = root_; // Returning a reference to the root
	return refRoot;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Removal Functions////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Destructor
*/
/******************************************************************************/
template<typename T>
BSTree<T>::~BSTree()
{
	clear();   // Clear the entire tree
	// Delete allocator if we created oru own
	if (ifShare == false && created == true)
		delete allocate;
}

/******************************************************************************/
/*!
	\brief
		Frees a node

	\param node
		Node to be freed
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::free_node(BinTree node) 
{ 
	node->~BinTreeNode();   // Calling the struct's destructor
	allocate->Free(node);   // Deallocate a node
}

/******************************************************************************/
/*!
	\brief
		Removes an item in the tree

	\param value
		Value to be removed
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::remove(const T& value) { DeleteItem(root_, value); }

/******************************************************************************/
/*!
	\brief
		Clears the tree
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::clear(void) { TraverseDelete(&root_); }

////////////////////////////////////////////////////////////////////////////////
////////////////////////////Height Functions////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Calculates the height of the tree and returns. Recursive function

	\param tree
		Tree of which we are trying to find the height

	\return
		Height
*/
/******************************************************************************/
template<typename T>
int BSTree<T>::tree_height(BinTree tree) const
{
	if (tree == 0)
		return -1;
	if (tree_height(tree->left) > tree_height(tree->right))
		return tree_height(tree->left) + 1; // Add up the height of the left tree
	return tree_height(tree->right) + 1;// Add up the height of the right tree
}

/******************************************************************************/
/*!
	\brief
		Finds predecessor

	\param tree
		Current tree

	\param predecessor
		Gives current predecessor
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::find_predecessor(BinTree tree, BinTree &predecessor) const
{
	predecessor = tree->left;
	while (predecessor->right != 0)
		predecessor = predecessor->right;
}

/******************************************************************************/
/*!
	\brief
		Finds the number of nodes in the tree

	\return
		Returns the number of nodes
*/
/******************************************************************************/
template<typename T>
unsigned int BSTree<T>::size(void) const
{
	if (root_ == NULL)
		return 0;
	return root_->count;  // Returning count of the top of the tree
}

/******************************************************************************/
/*!
	\brief
		Returns the height calculated by the tree height function

	\return
		The height
*/
/******************************************************************************/
template<typename T>
int BSTree<T>::height(void) const
{
	int h = tree_height(root_);
	return h;
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////Helper Functions from Website//////////////////////////
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Finding an item if it exists

	\param tree
		Tree to be looking in

	\param Data
		Data to be looking for

	\param compares
		Number of comparisons done while looking

	\return
		Returns if item exists
*/
/******************************************************************************/
template<typename T>
bool BSTree<T>::ItemExists(BinTree tree, T Data, unsigned &compares) const
{
	compares++;                 
	if (tree == 0)                   // If there is nothing in the tree, item isn't found
		return false;
	else if (Data == tree->data)     // If node is found
		return true;
	else if (Data < tree->data)      // If data is in the left of the tree
		return ItemExists(tree->left, Data, compares);
	else                             
		return ItemExists(tree->right, Data, compares); // If data is in the right of the tree
}

/******************************************************************************/
/*!
	\brief
		Inserts an item into the tree

	\param tree
		Tree to be inserted into

	\param Data
		Data the item has
*/
/******************************************************************************/
template <typename T>
void BSTree<T>::InsertItem(BinTree &tree, T Data)
{
	if (tree == 0)                // If there is nothing in the tree
		tree = make_node(Data);   // Make a new node
	else if (Data < tree->data)   // If data should be inserted in the left
	{
		(tree->count)++;
		InsertItem(tree->left, Data);
	}

	else if (Data > tree->data)   // If data should be inserted in the right
	{
		(tree->count)++;
		InsertItem(tree->right, Data);
	}
}

/******************************************************************************/
/*!
	\brief
		Deletes an item in the tree

	\param tree
		Tree to be deleted from

	\return Data
		Data to be deleted
*/
/******************************************************************************/
template <typename T>
void BSTree<T>::DeleteItem(BinTree &tree, T Data)
{
	if (tree == 0)                         // Return if tree is empty
		return;
	else if (Data < tree->data)            // If data is in the left subtree
	{
		DeleteItem(tree->left, Data);      // Go left
		(tree->count)--;                   // Decrement the count for that node
	}

	else if (Data > tree->data)            // If data is in the right subtree
	{
		DeleteItem(tree->right, Data);
		(tree->count)--;
	}

	else                                   // If the node is found
	{
		if (tree->left == 0)               // If you're at the end of the left subtree
		{
			BinTree temp = tree;
			tree = tree->right;          
			free_node(temp);
		}
		else if (tree->right == 0)         // If you're at the end of the right subtree
		{
			BinTree temp = tree;
			tree = tree->left;
			free_node(temp);
		}
		else                               // If you're not at the end of the branch     
		{
			BinTree pred = 0;
			find_predecessor(tree, pred);
			tree->data = pred->data;
			DeleteItem(tree->left, tree->data);
			(tree->count)--;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////Helper Functions/////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Traverses through the tree and sets all of the counts to the rhscount

	\param tree
		Tree that we are assigning to

	\param rhsTree
		Tree that we are assigning the values from
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::TraverseCounter(BinTree tree, BinTree rhsTree)
{
	if (tree == 0)    // If there is nothing in the tree
		return;             
	tree->count = rhsTree->count;                  // Assigning rhs count to this count
	TraverseCounter(tree->left, rhsTree->left);    // Traversing throught left
	TraverseCounter(tree->right, rhsTree->right);  // and right of the tree
}

/******************************************************************************/
/*!
	\brief
		Traversing through the tree and deleting all of the nodes

	\param tree
		Tree that we are deleting from
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::TraverseDelete(BinTree* tree)
{
	if (*tree)
	{
		TraverseDelete(&(*tree)->left);    // Traversing through left
		TraverseDelete(&(*tree)->right);   // and right of the tree
		allocate->Free(*tree);             // deallocating the node
		*tree = NULL;					   // Setting tree to NULL
	}
}

/******************************************************************************/
/*!
	\brief
		Recursive function that takes off nodes of the tree

	\param tree
		Tree to be chopped
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::chop(BinTree tree)
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
void BSTree<T>::copy(BinTree tree)
{
	if (!tree)              // If there is nothing in the tree, return
		return;
	BSTree<T>::insert(tree->data); // Insert the data into the tree
	copy(tree->left);              // Copy over new data into left tree
	copy(tree->right);
}

/************************************Extra Credit***************************************/
/******************************************************************************/
/*!
	\brief
		Subscript operator

	\param index
		Index to be found

	\return
		Returns BinTree at that index
*/
/******************************************************************************/
template<typename T>
const typename BSTree<T>::BinTreeNode* BSTree<T>::operator[](int index) const
{
	std::stack<BinTree*> nodes;           // Stack to hold the tree
	int count = 0;						  // Initializing the count to go through the stack
	BinTree root = root_;	
	Stack(root, nodes);				  // Calling recursive function to fill the stack
	std::stack<BinTree*> revNodes;        // Making a new stack to hold the reverse of the stack
	while (!nodes.empty())                // Reversing the stack
	{
		revNodes.push(nodes.top());
		nodes.pop();
	}
	while (!revNodes.empty())             // Going through the reversed stack
	{
		if (count == index)               // If the index is found
		{
			const BinTree* node = revNodes.top();  // Setting 
			return *node;
		}
		else
		{
			revNodes.pop();
			count++;
		}
	}

	return root_;
}

/******************************************************************************/
/*!
	\brief
		If extra credit is implemented

	\returns
		Returns if it's implemented
*/
/******************************************************************************/
template<typename T>
bool BSTree<T>::ImplementedIndexing(void) { return true; }

/******************************************************************************/
/*!
	\brief
		In order traversal of the tree to put all of the nodes in a stack

	\param tree
		Takes the tree to traverse

	\param nodes
		The stack to store the tree in
*/
/******************************************************************************/
template<typename T>
void BSTree<T>::Stack(BinTree& tree, std::stack<BinTree*> & nodes) const
{
	if (tree == 0)                   // Stop if at the end of the tree
		return;
	Stack(tree->left, nodes);        // In order traversal
	nodes.push(&tree);               // Push current node onto the 
	Stack(tree->right, nodes);
}
