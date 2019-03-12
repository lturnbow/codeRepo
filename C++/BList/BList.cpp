/******************************************************************************/
/*!
\file   BList.cpp
\author Lauren Turnbow
*/
/******************************************************************************/

/******************************************************************************/
/*!
	\brief
		Default Constructor
*/
/******************************************************************************/
template <typename T, int Size>
BList<T, Size>::BList() : head_(NULL), tail_(NULL), flag(true)
{
	// Flag is to indicate if the list is sorted. True is sorted
	// Initialize BListStatistics
	stats.NodeSize = sizeof(BNode);
	stats.ArraySize = Size;
	stats.NodeCount = 0;
	stats.ItemCount = 0;
}

/******************************************************************************/
/*!
	\brief
		Copy constructor
	\param rhs
		List to be copied
*/
/******************************************************************************/
template <typename T, int Size>
BList<T, Size>::BList(const BList& rhs)
{
	head_ = NULL;                        // Initializing current head and tail to NULL
	tail_ = NULL;
	flag = rhs.flag;
	stats.NodeSize = sizeof(BNode);      // Setting stats variables
	stats.ArraySize = Size;
	stats.NodeCount = 0;
	stats.ItemCount = 0;

	*this = rhs;             // Using assignment operator to copy list over
}



/******************************************************************************/
/*!
	\brief
		Assignment Operator
	\param rhs
		List to copy
	\return
		BList reference
*/
/******************************************************************************/
template <typename T, int Size>
typename BList<T, Size>::BList& BList<T, Size>::operator=(const BList& rhs)
{
	clear();                               // Clearing list to be copied into
	stats.ItemCount = rhs.stats.ItemCount; // Setting new stats variables
	stats.NodeCount = rhs.stats.NodeCount;
	stats.ArraySize = rhs.stats.ArraySize;

	BNode *rhsWalkThru = rhs.head_;        // Walkers for both lists
	BNode *walkThru = head_;

	// Making new node, setting it to head
	BNode *node = makeNode();
	head_ = node;
	walkThru = head_;

	// Copying data from rhs head into the new head
	for (int i = 0; i < rhsWalkThru->count; i++)
	{
		walkThru->values[i] = rhsWalkThru->values[i];
		(walkThru->count)++;
	}

	rhsWalkThru = rhsWalkThru->next;

	// Going through the rest of the given list
	while (rhsWalkThru)
	{
		BNode *node = makeNode();
		// If this is the last node in the list to be copied. Reset pointers
		if (rhsWalkThru == rhs.tail_)
		{
			tail_ = node;
			node->prev = walkThru;
			walkThru->next = node;
			walkThru = walkThru->next;
		}
		// If this is in the middle of the list. Reset pointers
		else
		{
			node->prev = walkThru;
			walkThru->next = node;
			walkThru = walkThru->next;
		}

		// Copy data over from rhs node to this node
		for (int i = 0; i < rhsWalkThru->count; i++)
		{
			walkThru->values[i] = rhsWalkThru->values[i];
			(walkThru->count)++;
		}
		rhsWalkThru = rhsWalkThru->next;
	}

	return *this;
}

/******************************************************************************/
/*!
	\brief
		Push back item to the end of list
	\param value
		Value to insert
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::push_back(const T& value)
{
	// Set flag to false because push back will cause the list to be unsorted
	flag = false;
	if (head_ == NULL)
	{
		BNode *node = makeNode();   // Make a new node with the current value
		stats.NodeCount++;
		node->values[0] = value;
		node->next = NULL;          // Reset pointers. This is the only node in list
		node->prev = NULL;
		head_ = node;
		tail_ = node;
	}

	BNode *node = tail_;            // Going to the back of the list to push onto

	if (node->count < Size)   // If last node is not full, place at the end of last node
	{
		node->values[node->count] = value;
		stats.ItemCount++;
		(node->count)++;
	}

	else if (node->count == Size)        // If the last node is full
	{
		BNode *node = makeNode();   // Make a new node and put value in
		stats.NodeCount++;
		node->values[0] = value;
		stats.ItemCount++;
		tail_->next = node;        // Reset pointers. Make this node the tail
		node->prev = tail_;
		node->next = NULL;
		tail_ = node;
		(node->count++);
	}
}

/******************************************************************************/
/*!
	\brief
		Puts value at beginning of list
	\param
		Value to insert
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::push_front(const T& value)
{
	flag = false;                     // List is now unsorted
	if (head_ == NULL)
	{
		BNode *node = makeNode();     // If list is empty make new node and place value
		stats.NodeCount++;
		node->values[0] = value;
		node->next = NULL;            // Set pointers
		node->prev = NULL;
		head_ = node;
		tail_ = node;
	}

	BNode *node = head_;              // Set pointer to head to put value in front of it

	if (node->count < Size)      // If there is room in the head node, place at front of node
	{
		for (int i = node->count; i > 0; i--)
			node->values[i] = node->values[i - 1];
		node->values[0] = value;
		stats.ItemCount++;
		(node->count)++;
	}

	else if (node->count == Size)          // If head is full
	{
		BNode *node = makeNode();     // Make a new node and place value in it
		stats.NodeCount++;
		node->values[0] = value;
		stats.ItemCount++;
		node->next = head_;           // Set pointers to put new node as head
		node->prev = NULL;
		head_->prev = node;
		head_ = node;
		(node->count)++;
	}
}

/******************************************************************************/
/*!
	\brief
		Finds value in the list
	\param value
		Value to be found
	\return
		Returns the index of the value
*/
/******************************************************************************/
template <typename T, int Size>
int BList<T, Size>::find(const T& value) const
{
	if (flag == false)                // If list is unsorted
	{
		if (head_ == NULL || head_->values[0] == value)
			return 0;

		int count = 0;
		BNode *walkThru = head_;
		while (walkThru)
		{
			// Go through the list
			for (int i = 0; i < walkThru->count; i++)
			{
				count++;  // To keep track of the total elements that have been gone through
				if (walkThru->values[i] == value)  // If the value is found
					return count - 1;              // Return the index
			}
			walkThru = walkThru->next;
		}
		return -1;								   // Return -1 if the value was not found
	}

	else                                 // Perform a binary search if the list is sorted
	{
		if (head_ == NULL || head_->values[0] == value)
			return 0;

		int lowerbound = 0;						 // First item in the list
		int upperbound = stats.ItemCount - 1;    // Last index in the list
		int position = (lowerbound + upperbound) / 2;   // Middle value of the list
														// Going through the list while hte value is not found and the lowerbound is less than the upperbound
		while (!((*this)[position] == value) && (lowerbound <= upperbound))
		{
			if (value < (*this)[position])     // If value is less than the middle
				upperbound = position - 1;
			else                               // If value is greater than the middle
				lowerbound = position + 1;
			position = (lowerbound + upperbound) / 2;  // Find a new middle by splitting in half again
		}

		if (lowerbound > upperbound)     // The value was not found
			return -1;
		else                             // The value was found
			return position;
	}
	return -1;
}

/******************************************************************************/
/*!
	\brief
		Finds value at given index
	\param index
		Index to be found
	\return
		Returns value at that index
*/
/******************************************************************************/
template <typename T, int Size>
T& BList<T, Size>::operator[](int index)
{
	BNode *walkThru = head_;
	int counter = 0;
	// If a bad index was given
	if (index < 0 || index >= stats.ItemCount)
		throw(BListException(BListException::E_BAD_INDEX, "BAD INDEX"));

	while (walkThru)
	{
		counter += walkThru->count;      // Adding current node count to the counter
		if (counter > index)			 // If counter is greater than the index, index is in the current node
		{
			counter -= walkThru->count;  // If node is found, subtract what was just added to start at beginning of node
			return walkThru->values[index - counter];   // Return the value at that position
		}

		walkThru = walkThru->next;
	}

	throw(BListException(BListException::E_BAD_INDEX, "BAD INDEX"));
	return walkThru->values[0];
}

/******************************************************************************/
/*!
	\brief
		Finds value at given index
	\param index
		Index to be found
	\return
		Returns value at that index
*/
/******************************************************************************/
template <typename T, int Size>
const T& BList<T, Size>::operator[](int index) const
{
	BNode *walkThru = head_;
	int counter = 0;
	// If a bad index was given
	if (index < 0 || index >= stats.ItemCount)
		throw(BListException(BListException::E_BAD_INDEX, "BAD INDEX"));

	while (walkThru)
	{
		counter += walkThru->count;      // Adding current node count to the counter
		if (counter > index)			 // If counter is greater than the index, index is in the current node
		{
			counter -= walkThru->count;  // If node is found, subtract what was just added to start at beginning of node
			return walkThru->values[index - counter];   // Return the value at that position
		}

		walkThru = walkThru->next;
	}

	throw(BListException(BListException::E_BAD_INDEX, "BAD INDEX"));
	return walkThru->values[0];
}

/******************************************************************************/
/*!
	\brief
		Inserts value into a sorted list
	\param value
		Value to insert
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::insert(const T& value)
{
	if (head_ == NULL)             // If list is empty, insert value into node and place on list
	{
		BNode *node = makeNode();
		stats.NodeCount++;
		node->values[0] = value;
		head_ = node;             // Set pointers
		tail_ = node;
		head_->next = NULL;
		head_->prev = NULL;
		(node->count)++;          // Increment counts
		stats.ItemCount++;
		return;
	}

	// If there is only one node in the list and the arraySize is greater than 1
	if (head_ == tail_ && stats.ArraySize != 1)
	{
		// If the node is full, split the node and reset the pointer
		if (head_->count == Size)
		{
			head_ = splitNode(head_, value);
			tail_ = head_->next;
		}

		// If there is room in the node, insert the value either into the front
		// middle, or end depending on the value
		else if (head_->count < Size)
		{
			if (value < head_->values[0])
				insertFront(head_, value);

			else if (head_->values[head_->count - 1] < value)
				insertEnd(head_, value);

			else
				insertMiddle(head_, value);
			increaseCount(head_);
		}
		return;
	}

	BNode* walkThru = head_;
	while (walkThru)
	{
		int count = walkThru->count;
		// If array size is 1 and we are at the end of the list and the first value is
		// less than the value, make a new node and place it at the end of the list
		if (stats.ArraySize == 1 && walkThru->next == NULL && walkThru->values[0] < value)
		{
			BNode *node = makeNode(); // Make a new node and set it to the value
			stats.NodeCount++;
			node->values[0] = value;
			walkThru->next = node;    // Reset pointers to place node at the end of the list
			walkThru->prev = NULL;
			node->next = NULL;
			node->prev = walkThru;
			tail_ = node;
			tail_->next = NULL;
			tail_->prev = walkThru;
			increaseCount(node);
			return;
		}

		// If array size is 1, we are at the head, and the value is less than the first 
		// value in the head. Insert new node with value in the front
		else if (stats.ArraySize == 1 && walkThru == head_ && value < walkThru->values[0])
		{
			BNode *node = makeNode();   // Make new node
			stats.NodeCount++;
			node->values[0] = value;
			node->next = walkThru;      // Reset pointers
			node->prev = NULL;
			walkThru->prev = node;
			head_ = node;
			head_->prev = NULL;
			head_->next = walkThru;
			increaseCount(node);
			return;
		}

		// If array size is 1 and the value is greater than the first value and less than the first
		// value of the next node. Insert new node in between these two
		else if (stats.ArraySize == 1 && walkThru->values[0] < value && value < walkThru->next->values[0])
		{
			BNode *node = makeNode();      // Make new node
			stats.NodeCount++;
			node->values[0] = value;
			BNode *temp = walkThru->next;  // Set pointers to place node in the middle of these two nodes
			walkThru->next = node;
			node->prev = walkThru;
			temp->prev = node;
			node->next = temp;
			increaseCount(node);
			return;
		}

		///////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (stats.ArraySize != 1)
		{
			// If the value is less than the last value in the node that means that the value should go in that node
			// Also check if the next is null to prevent comparing with nodes that don't exist
			if (value < walkThru->values[count - 1] || walkThru->next == NULL)
			{
				if (walkThru->next == NULL)
				{
					// If there is room in the previous node and and the value can go between the last node and 
					// the start of the first node, place value in the last node
					if (walkThru->prev != NULL && walkThru->prev->count < Size && walkThru->prev->values[walkThru->prev->count - 1] < value
						&& value < walkThru->values[0])
					{
						insertEnd(walkThru->prev, value);   // Insert value at the end of the previous node
						increaseCount(walkThru->prev);
						return;
					}

					// If the current node is full and the previous node exists but is full, and the value can go
					// between these two nodes, split the node
					else if (walkThru->prev != NULL && walkThru->count == Size && walkThru->prev->count == Size &&
						value < walkThru->values[0] && walkThru->prev->values[walkThru->prev->count - 1] < value)
					{
						walkThru->prev = splitNode(walkThru->prev, value);   // Split the previous node
						return;
					}

					// If the current node is not full, insert value into the node depending on the value
					else if (count < Size)
					{
						if (value < walkThru->values[0])    // If value is less than the first value, insert in the front
							insertFront(walkThru, value);

						else if (walkThru->values[count - 1] < value)  // If value is greater than last value insert to end
							insertEnd(walkThru, value);

						else
							insertMiddle(walkThru, value);			   // If value is between nodes in the middle, insert there

						increaseCount(walkThru);
						return;
					}

					// If the node is full, split the node and insert the value
					else if (count == Size)
						walkThru = splitNode(walkThru, value);
					return;
				}

				// If the node is full and the previos node exists but is also full and the value can fit between the 
				// first and previous nodes, split the previous node
				else if (walkThru->prev != NULL && walkThru->count == Size && walkThru->prev->count == Size &&
					value < walkThru->values[0] && walkThru->prev->values[walkThru->prev->count - 1] < value)
				{
					walkThru->prev = splitNode(walkThru->prev, value);
					return;
				}

				// If the current node isn't full and the previous node exists and there is also room in the previous
				// node, and the value can fit between the two, insert into the end of the previous node
				else if (walkThru->prev != NULL && walkThru->count < Size && walkThru->prev->count < Size
					&& walkThru->prev->values[walkThru->prev->count - 1] < value && value < walkThru->values[0])
				{
					insertEnd(walkThru->prev, value);
					increaseCount(walkThru->prev);
					return;
				}

				// If the current node is full and the previous node exists and there is room in the previous node and
				// the value can fit between the two, insert into the end of the previous node
				else if (walkThru->count == Size && walkThru->prev != NULL && walkThru->prev->count < Size
					&& walkThru->prev->values[walkThru->prev->count - 1] < value && value < walkThru->values[0])
				{
					insertEnd(walkThru->prev, value);
					increaseCount(walkThru->prev);
					return;
				}

				// If there is room in the current node, put the value in the current node, insert into the front, middle,
				// or end depending on the value
				else if (count < Size)
				{
					if (value < walkThru->values[0])
						insertFront(walkThru, value);

					else if (walkThru->values[count - 1] < value && value < walkThru->next->values[0])
						insertEnd(walkThru, value);

					else
						insertMiddle(walkThru, value);
					increaseCount(walkThru);
					return;
				}

				// If the node is full, split the node
				else if (count == Size)
				{
					walkThru = splitNode(walkThru, value);
					return;
				}
			}
		}
		walkThru = walkThru->next;
	}
}

/******************************************************************************/
/*!
	\brief
		Removes value at a given index
	\param index
		Index to remove value at
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::remove(int index)
{
	BNode *walkThru = head_;
	int counter = walkThru->count - 1;

	// If given a negative index or the index is outside of the bounds of the list
	if (index < 0 || index >= stats.ItemCount)
		throw(BListException(BListException::E_BAD_INDEX, "BAD INDEX"));

	// Go through until the counter is greater than the index, then the index is in that node
	while (counter < index)
	{
		walkThru = walkThru->next;
		counter += walkThru->count;
	}

	// Subtract the count that was just added to go to the beginning of the given node
	counter -= walkThru->count - 1;

	// Don't shift values down in the array if there is only one value in the array
	if (stats.ArraySize != 1)
	{
		// Shift the values down to take out the value that is to be removed
		for (int i = index - counter; i < walkThru->count; i++)
			walkThru->values[i] = walkThru->values[i + 1];
	}

	decreaseCount(walkThru);
	walkThru = head_;

	// Removing nodes if they don't have anything in them
	// Removing the head if the count is 0 and resetting the pointers
	if (head_->count == 0)
	{
		BNode* temp = head_->next;
		delete head_;
		head_ = temp;
		head_->prev = NULL;
		stats.NodeCount--;
	}

	// Removing the tail if it's empty
	if (tail_->count == 0)
	{
		BNode *temp = tail_->prev;
		delete tail_;
		tail_ = temp;
		tail_->next = NULL;
		stats.NodeCount--;
	}
	walkThru = head_;

	// Going through the list and finding any other nodes that are empty
	while (walkThru)
	{
		if (walkThru->count == 0)
		{
			BNode* temp = walkThru->next;      // Deleting the empty node
			BNode* tempPrev = walkThru->prev;
			delete walkThru;
			walkThru = temp;                   // Resetting the pointers
			walkThru->prev = tempPrev;
			tempPrev->next = walkThru;
			stats.NodeCount--;
		}
		walkThru = walkThru->next;
	}
}

/******************************************************************************/
/*!
	\brief
		Removes specified value
	\param value
		Value to be removed
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::remove_by_value(const T& value)
{
	BNode *walkThru = head_;
	while (walkThru)
	{
		for (int i = 0; i < walkThru->count; i++)
		{
			if (walkThru->values[i] == value && stats.ArraySize != 1)     // If value is found
			{
				for (int j = i; j < walkThru->count; j++)    // Shift all values down
					walkThru->values[j] = walkThru->values[j + 1];

				decreaseCount(walkThru);
			}

			if (walkThru->values[i] == value && stats.ArraySize == 1)
				decreaseCount(walkThru);

		}
		walkThru = walkThru->next;
	}

	// Removing nodes if they don't have anything in them
	// Removing the head if the count is 0 and resetting the pointers
	if (head_->count == 0)
	{
		BNode* temp = head_->next;
		delete head_;
		head_ = temp;
		head_->prev = NULL;
		stats.NodeCount--;
	}

	// Removing the tail if it's empty
	if (tail_->count == 0)
	{
		BNode *temp = tail_->prev;
		delete tail_;
		tail_ = temp;
		tail_->next = NULL;
		stats.NodeCount--;
	}
	walkThru = head_;
	// Going through the list and finding any other nodes that are empty
	while (walkThru)
	{
		if (walkThru->count == 0)
		{
			BNode* temp = walkThru->next;
			BNode* tempPrev = walkThru->prev;
			delete walkThru;
			walkThru = temp;
			walkThru->prev = tempPrev;
			tempPrev->next = walkThru;
			stats.NodeCount--;
		}
		walkThru = walkThru->next;
	}
}

/******************************************************************************/
/*!
	\brief
		Deletes all nodes in the list
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::clear(void)
{
	if (head_ == NULL)       // If head is null, there is nothing to clear
		return;
	while (head_)            // While there is a list
	{
		if (head_ == tail_)  // If there's only one node in the list
		{
			delete head_;
			break;
		}

		BNode* temp = head_->next; // Deleting all nodes
		delete head_;              // Delete current node
		head_ = temp;              // Reset pointers
		head_->prev = NULL;

		head_ = head_->next;
	}
	stats.ItemCount = 0;          // Setting stats to 0
	stats.NodeCount = 0;
	head_ = NULL;
	tail_ = NULL;
	flag = true;
}

/******************************************************************************/
/*!
	\brief
		Destructor
*/
/******************************************************************************/
template <typename T, int Size>
BList<T, Size>::~BList()
{
	clear();                 // Deleting everything in the list
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////HELPER FUNCTIONS////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Splits node and puts value into correct psotion
	\param node
		Node to be split
	\param value
		Value to be inserted into split node
	\return
		Returns a pointer to the first node that is split
*/
/******************************************************************************/
template <typename T, int Size>
typename BList<T, Size>::BNode* BList<T, Size>::splitNode(BNode* node, const T value)
{
	// Making new nodes to put node that will be split into
	BNode *node1 = makeNode();
	BNode *node2 = makeNode();
	stats.NodeCount++;

	int j = 0;
	// Placing first half of data into first node
	for (int i = 0; i < (node->count) / 2; i++)
	{
		node1->values[j] = node->values[i];
		(node1->count)++;
		j++;
	}

	j = 0;
	// Placing second half of data into second node
	for (int i = (node->count) / 2; i < node->count; i++)
	{
		node2->values[j] = node->values[i];
		(node2->count)++;
		j++;
	}

	// Inserting value into one of the two split nodes. If the value is less than all of the
	// values in the second node, it's in the first node. If it's not, it's in the second
	// node
	if (value < node2->values[0])
	{
		if (value < node1->values[0])   // If the value is less than the first value
			insertFront(node1, value);  // Insert into the front

										// If value is greater than the last value and less than the value of first
										// value in the next node, insert into the end of the first node
		else if (node1->values[node1->count - 1] < value && value < node2->values[0])
			insertEnd(node1, value);

		// If not at the front or end, insert somewhere in the middle of the node
		else
			insertMiddle(node1, value);

		(node1->count)++;
	}

	// Inserting into the second node
	else
	{
		if (value < node2->values[0])
			insertFront(node2, value);

		else if (node2->values[node2->count - 1] < value)
			insertEnd(node2, value);

		else
			insertMiddle(node2, value);

		(node2->count)++;
	}
	stats.ItemCount++;
	// Updating the pointers, keeping track of the original node's next and previous pointers
	BNode* prev = node->prev;
	BNode* next = node->next;

	// If nothing was behind or in front of the given node
	if (prev == NULL && next == NULL)
	{
		node1->next = node2;   // Set pointers
		node2->prev = node1;
		node1->prev = NULL;
		node2->prev = node1;
	}

	// If nothing was behind the given node
	else if (prev == NULL && next != NULL)
	{
		node1->next = node2;
		node2->prev = node1;
		node1->prev = NULL;
		node2->next = next;
		next->prev = node2;
	}

	// If nothing was in front of the given node
	else if (prev != NULL && next == NULL)
	{
		node1->next = node2;
		node2->prev = node1;
		prev->next = node1;
		node1->prev = prev;
		node2->next = NULL;
	}

	// If there were nodes pointing to and from the given node
	else if (prev != NULL && next != NULL)
	{
		node1->next = node2;
		node2->prev = node1;
		prev->next = node1;
		node1->prev = prev;
		node2->next = next;
		next->prev = node2;
	}

	// Resetting the head and tail if the given node was a head or tail
	if (node == head_)
		head_ = node1;

	if (node == tail_)
		tail_ = node2;

	delete node;     // Deleting the given node
	return node1;
}

/******************************************************************************/
/*!
	\brief
		Makes a new node
	\return
		A pointer to the new node
*/
/******************************************************************************/
template <typename T, int Size>
typename BList<T, Size>::BNode* BList<T, Size>::makeNode()
{
	BNode *node = 0;
	try { node = new BNode; }           // Allocating a new node
	catch (const std::exception& e) {   // Throw exception if node can't be allocated
		throw(BListException(BListException::E_NO_MEMORY, e.what()));
	}
	return node;
}

/******************************************************************************/
/*!
	\brief
		Updates the count of the given node and the itemcount
	\param node
		The node that will have the count updated
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::increaseCount(BNode *node)
{
	(node->count)++;
	stats.ItemCount++;
}

/******************************************************************************/
/*!
	\brief
		Updates the count of the given node and the itemcount
	\param node
		The node that will have the count updated
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::decreaseCount(BNode *node)
{
	(node->count)--;
	stats.ItemCount--;
}

/******************************************************************************/
/*!
	\brief
		Inserts value into the front of the given node
	\param node
		Node to be inserted into
	\param value
		Value to be inserted
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::insertFront(BNode* node, const T value)
{
	// Inserting in to the front of the node by shifting all values to the right
	// by one and inserting value at the very front
	for (int i = node->count; i > 0; i--)
		node->values[i] = node->values[i - 1];
	node->values[0] = value;
}

/******************************************************************************/
/*!
	\brief
		Inserts at the end of a node
	\param node
		Node to be inserted into
	\param value
		Value to be inserted
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::insertEnd(BNode* node, const T value)
{
	node->values[(node->count)] = value; // Inserting value at the end of the array
}

/******************************************************************************/
/*!
	\brief
		Inserts into the middle of a given node
	\param node
		Node to be inserted into
	\param value
		Value to be inserted
*/
/******************************************************************************/
template <typename T, int Size>
void BList<T, Size>::insertMiddle(BNode* node, const T value)
{
	for (int i = 0; i < node->count; i++)
	{
		// Finding where the value should go
		if (node->values[i] < value && value < node->values[i + 1])
		{
			// Shifting all nodes down from there
			for (int j = node->count; j > i + 1; j--)
				node->values[j] = node->values[j - 1];
			// Inserting value at specified position
			node->values[i + 1] = value;
			return;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Returns the head of the list
	\return
		The head
*/
/******************************************************************************/
template <typename T, int Size>
const typename BList<T, Size>::BNode* BList<T, Size>::GetHead() const
{
	return head_;
}

/******************************************************************************/
/*!
	\brief
		Returns the stats struct
	\return
		Current stats
*/
/******************************************************************************/
template <typename T, int Size>
BListStats BList<T, Size>::GetStats(void) const
{
	return stats;
}

/******************************************************************************/
/*!
	\brief
		Returns the nodesize
	\return
		Returns the nodesize
*/
/******************************************************************************/
template <typename T, int Size>
size_t BList<T, Size>::nodesize(void)
{
	return sizeof(BNode);
}

/******************************************************************************/
/*!
	\brief
		Returns number of elements in the list
	\return
		Returns number of elements in the list
*/
/******************************************************************************/
template <typename T, int Size>
size_t BList<T, Size>::size(void) const
{
	size_t counter = 0;

	BNode* walkThru = head_;
	while (walkThru)				 // Going through the list
	{
		counter += walkThru->count;  // Adding the current count to the counter
		walkThru = walkThru->next;
	}

	return counter;
}
