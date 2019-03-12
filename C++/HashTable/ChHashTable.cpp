/******************************************************************************/
/*!
\file   ChHashTable.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include <cmath>
#include "ChHashTable.h"

/******************************************************************************/
/*!
	\brief
		Returns the current stats for the has table

	\return
		Returns a stats struct
*/
/******************************************************************************/
template<typename T>
HTStats ChHashTable<T>::GetStats() const { return stats; }

/******************************************************************************/
/*!
	\brief
		Returns the hash table

	\return
		Returns a head node pointer
*/
/******************************************************************************/
template<typename T>
const typename ChHashTable<T>::ChHTHeadNode* ChHashTable<T>::GetTable() const { return table_; }

/******************************************************************************/
/*!
	\brief
		ChHashTable constructor

	\param Config
		Config struct

	\param allocator
		Allocator that will be used
*/
/******************************************************************************/
template<typename T>
ChHashTable<T>::ChHashTable(const HTConfig& Config, ObjectAllocator* allocator)
	: config_(Config), created_(false), table_(NULL), head_(), stats()
{
	if (allocator == 0)                  // Not creating an objectallocator
		created_ = false;

	else
	{
		stats.Allocator_ = allocator;    // Creating an object allocator
		created_ = true;
	}

	table_ = new ChHTHeadNode[config_.InitialTableSize_]; // Initializing the table with the given size
	stats.TableSize_ = config_.InitialTableSize_;
	stats.Count_ = 0;                                     // Initializing counting variables to 0
	stats.Probes_ = 0;
	stats.Expansions_ = 0;
}

/******************************************************************************/
/*!
	\brief
		Grows the hash table 
*/
/******************************************************************************/
template<typename T>
void ChHashTable<T>::GrowTable() 
{
	double factor = std::ceil(stats.TableSize_ * config_.GrowthFactor_);  // Expanding the table
	unsigned new_size = GetClosestPrime(static_cast<unsigned>(factor));   // Calculating new size of the table

	ChHTHeadNode* oldTable = table_;           // Keeping a pointer to the old table
	unsigned oldTableSize = stats.TableSize_;  // Keeping the old table size
	stats.TableSize_ = new_size;               // Resetting the table size in the stats struct
	table_ = new ChHTHeadNode[new_size];       // Resizing the table
	
	unsigned hash = 0;
	while (hash < oldTableSize)                // Going through all of the old table
	{
		while ((oldTable[hash]).Nodes != NULL) // Going through the individual nodes of each position in the old table
		{
			// Recalculating the new hash index according to the new table size for each Key
			unsigned newHash = config_.HashFunc_((oldTable[hash]).Nodes->Key, new_size);

			ChHTNode* oldTableNext = (oldTable[hash]).Nodes->Next; // Keeping a pointer to the next of the old table
			// Switching the pointers around to put the nodes in the new hash table at the new positions
			(oldTable[hash]).Nodes->Next = (table_[newHash]).Nodes;
			(table_[newHash]).Nodes = (oldTable[hash]).Nodes;
			(oldTable[hash]).Nodes = oldTableNext;
		}
		hash++;
	}
	
	stats.Expansions_++;   
	delete[] oldTable;
}

/******************************************************************************/
/*!
	\brief
		Inserts a key/data pair into the table. Throws an exception if the
		insertion is unsuccessful

	\param Key
		Key to insert

	\param Data
		Data to insert
*/
/******************************************************************************/
template<typename T>
void ChHashTable<T>::insert(const char *Key, const T& Data)
{
	// Checking if the table needs to be expanding by seeing if inserting one would
	// cause the load factor to go over the max load factor
	if (((stats.Count_ + 1.0) / stats.TableSize_) > config_.MaxLoadFactor_)
		GrowTable();

	unsigned hash = config_.HashFunc_(Key, stats.TableSize_);   // Calculating the hash function
	if ((table_[hash]).Nodes == NULL)                // If the nodes linked list is NULL
	{
		ChHTNode* newNode;                           // Allocate a new node, using the allocator or new
		if (created_ == false) 
			newNode = new ChHTNode(Data);
		else if (created_ == true)
		{
			try
			{
				ChHTNode* node = reinterpret_cast<ChHTNode*>(stats.Allocator_->Allocate());
				newNode = new (node) ChHTNode(Data);
			}
			catch (const OAException &e)
			{
				throw(HashTableException(HashTableException::E_NO_MEMORY, e.what()));
			}
		}

		strcpy(newNode->Key, Key);               // Insert the key
		(table_[hash]).Nodes = newNode;          // Put the allocated node in the list of nodes
		newNode->Next = NULL;
		stats.Probes_++;
		stats.Count_++;
	}

	else                                         // If the nodes linked list is not NULL
	{
		ChHTNode* walker = (table_[hash]).Nodes;
		while (walker != NULL)                  // Walk through the linked list and check for duplicates
		{
			if (!strcmp(Key, walker->Key))      // If there is a duplicate, throw an exception
				throw(HashTableException(HashTableException::E_DUPLICATE, "Duplicate"));

			walker = walker->Next;
			stats.Probes_++;
		}

		ChHTNode* newNode;                     // If the key is unique, create a new node
		if (created_ == false) 
			newNode = new ChHTNode(Data);
		else if (created_ == true)
		{
			try
			{
				ChHTNode* node = reinterpret_cast<ChHTNode*>(stats.Allocator_->Allocate());
				newNode = new (node) ChHTNode(Data);
			}
			catch (const OAException &e)
			{
				throw(HashTableException(HashTableException::E_NO_MEMORY, e.what()));
			}
		}

		strcpy(newNode->Key, Key);            // Insert the key into the new node
		stats.Probes_++;
		stats.Count_++;

		newNode->Next = (table_[hash]).Nodes; // Insert the node at the front of the nodes linked list
		(table_[hash]).Nodes = newNode;

		(table_[hash]).Nodes->Data = Data;    // Insert the data into the node
	}
}

/******************************************************************************/
/*!
	\brief
		Finds and returns the data by key. Throws an exception if the key 
		doesn't exist

	\param Key
		The key that is being searched for

	\return
		Returns the data associated with the Key
*/
/******************************************************************************/ 
template<typename T>
const T& ChHashTable<T>::find(const char *Key) const
{
	unsigned hash = config_.HashFunc_(Key, stats.TableSize_);   // Calculating hash
	if ((table_[hash]).Nodes == NULL)                           // If the list is null, the key isn't in there
		throw(HashTableException(HashTableException::E_ITEM_NOT_FOUND, "NotFound"));

	ChHTNode* walker = (table_[hash]).Nodes;
	while (walker != NULL && strcmp(Key, walker->Key))  // Walking through list until they key is found
	{
		stats.Probes_++;
		walker = walker->Next;
	}

	if (walker != NULL && !strcmp(Key, walker->Key))    // If they key is found, return the data
	{
		stats.Probes_++;
		return walker->Data;
	}

	if (walker == NULL)                 // If they key isn't found, end of list is reached, throw exception
		throw(HashTableException(HashTableException::E_ITEM_NOT_FOUND, "NotFound"));

	return NULL;
}

/******************************************************************************/
/*!
	\brief
		Deletes an item by Key. Throws an exception if the key doesn't exist

	\param Key
		Key of the item to be deleted
*/
/******************************************************************************/
template<typename T>
void ChHashTable<T>::remove(const char *Key)
{
	unsigned hash = config_.HashFunc_(Key, stats.TableSize_);

	if ((table_[hash]).Nodes == NULL)           // If list is NULL, there is nothing left to remove
		return;

	ChHTNode* walker = (table_[hash]).Nodes;

	while (walker != NULL && strcmp(Key, walker->Key))  // Walk through list looking for key
	{
		stats.Probes_++;
		if (!strcmp(Key, (walker->Next->Key)))          // If the next key is the key we're looking for
		{
			ChHTNode* prevEntry = walker;               // Hold onto current position
			ChHTNode* nextNode = walker->Next->Next;    // The next next is the one we want to link the previous to
			if (config_.FreeProc_ != 0)
				config_.FreeProc_(walker->Next->Data);
			if (created_ == false)                      // Delete the next position
				delete walker->Next;
			else if (created_ == true) 
				stats.Allocator_->Free(walker->Next);
			
			prevEntry->Next = nextNode;                 // Reset the pointers

			stats.Count_--;
			stats.Probes_++;
			return;
		}
		walker = walker->Next;
	}

	if (!strcmp(Key, (table_[hash]).Nodes->Key))        // If the key is at the beginning of the list
	{
		stats.Probes_++;
		ChHTNode* nextEntry = (table_[hash]).Nodes->Next;  // Hold onto the second position in the list
		if (config_.FreeProc_ != 0)
			config_.FreeProc_((table_[hash]).Nodes->Data);
		if (created_ == false)                             // Delete the first position
			delete (table_[hash]).Nodes;
		else if (created_ == true)
			stats.Allocator_->Free((table_[hash]).Nodes);  // Set the next position to be the first in the list
		(table_[hash]).Nodes = nextEntry;
		stats.Count_--;
	}
}

/******************************************************************************/
/*!
	\brief
		Removes all items from the table. Doesn't deallocate the table
*/
/******************************************************************************/
template<typename T>
void ChHashTable<T>::clear()
{
	unsigned i = 0;
	while (i < stats.TableSize_)            // Going through the whole table
	{
		if (&(table_[i]) != NULL)           // If the table at this position is NULL
		{
			ChHTNode* prevEntry;
			while ((table_[i]).Nodes != NULL)  // Going through the linked list of nodes at this table location
			{
				prevEntry = (table_[i]).Nodes; // Holding onto the prev entry
				(table_[i]).Nodes = (table_[i]).Nodes->Next;  // Moving the node up one to override the previous node
				if (config_.FreeProc_ != 0)
					config_.FreeProc_(prevEntry->Data);
				if (created_ == false)         // Delete the previous
					delete prevEntry;
				else
					stats.Allocator_->Free(prevEntry);
				stats.Count_--;
			}
		}
		i++;
	}
}

/******************************************************************************/
/*!
	\brief
		Destructor
*/
/******************************************************************************/
template<typename T>
ChHashTable<T>::~ChHashTable()
{
	clear();                 // Clear the whole table
	delete[] table_;         // Delete the table
}

