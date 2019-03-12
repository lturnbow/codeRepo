/******************************************************************************/
/*!
\file   AVLTree.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS280
\par    Assignment #4
\date   3/26/2017
*/
/******************************************************************************/
//---------------------------------------------------------------------------
#ifndef AVLTREE_H
#define AVLTREE_H
//---------------------------------------------------------------------------
#include <stack>
#include "BSTree.h"

template <typename T>
class AVLTree : public BSTree<T>
{
  public:
    AVLTree(ObjectAllocator *OA = 0, bool ShareOA = false);
    virtual ~AVLTree();
    virtual void insert(const T& value);
    virtual void remove(const T& value);

	static bool ImplementedBalanceFactor();

	void InsertAVLItem2(typename BSTree<T>::BinTree& tree, T Data, std::stack<typename BSTree<T>::BinTree*> & nodes);
	void RecursiveInsert(const T& value);
	void BalanceAVLTree(std::stack<typename BSTree<T>::BinTree*> & nodes);

	void RotateLeft(typename BSTree<T>::BinTree& node);
	void RotateRight(typename BSTree<T>::BinTree& node);
	int SubTreeCount(typename BSTree<T>::BinTree leaf) const;

protected:
	void AVLTraverseCounter(typename BSTree<T>::BinTree tree);
	void chop(typename BSTree<T>::BinTree tree);
	void copy(typename BSTree<T>::BinTree tree);
	void Delete(typename BSTree<T>::BinTree &tree, T data, std::stack<typename BSTree<T>::BinTree*>& delNodes);
	void RecursiveDelete(const T& value);
};

#include "AVLTree.cpp"
#endif