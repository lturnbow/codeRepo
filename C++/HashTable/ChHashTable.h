/******************************************************************************/
/*!
\file   ChHashTable.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS280
\par    Assignment #5
\date   4/13/2017
*/
/******************************************************************************/
#ifndef OAHASHTABLEH
#define OAHASHTABLEH

#include <string>
#include "ObjectAllocator.h"
#include "support.h"
#include <iostream>

typedef unsigned(*HASHFUNC)(const char *, unsigned);  // client-provided hash function: takes a key and table size, returns an index in the table
const unsigned MAX_KEYLEN = 10;      // Max length of our "string" keys

class HashTableException
{
private:
	int error_code_;
	std::string message_;

public:
	HashTableException(int ErrCode, const std::string& Message) : error_code_(ErrCode), message_(Message) {};
	virtual ~HashTableException() {  }
	virtual int code() const { return error_code_; }
	virtual const char *what() const { return message_.c_str(); }
	enum HASHTABLE_EXCEPTION { E_ITEM_NOT_FOUND, E_DUPLICATE, E_NO_MEMORY };

};

struct HTStats        // HashTable statistical info
{
	HTStats() : Count_(0), TableSize_(0), Probes_(0), Expansions_(0), HashFunc_(0), Allocator_(0) {};///////////////Take out allocator
	unsigned Count_;      // Number of elements in the table
	unsigned TableSize_;  // Size of the table (total slots)
	mutable unsigned Probes_;     // Number of probes performed
	unsigned Expansions_; // Number of times the table grew
	HASHFUNC HashFunc_;   // Pointer to primary hash function
	ObjectAllocator *Allocator_; // The allocator in use (may be 0)
};

template <typename T>
class ChHashTable
{
public:
	typedef void(*FREEPROC)(T); // client-provided free proc (we own the data)
	struct HTConfig
	{
		HTConfig(unsigned InitialTableSize, HASHFUNC HashFunc, double MaxLoadFactor = 3.0, double GrowthFactor = 2.0, FREEPROC FreeProc = 0)
			: InitialTableSize_(InitialTableSize), HashFunc_(HashFunc), MaxLoadFactor_(MaxLoadFactor), GrowthFactor_(GrowthFactor), FreeProc_(FreeProc) {}
		unsigned InitialTableSize_;
		HASHFUNC HashFunc_;
		double MaxLoadFactor_;
		double GrowthFactor_;
		FREEPROC FreeProc_;
	};

	struct ChHTNode        // Nodes that will hold the key/data pairs
	{
		char Key[MAX_KEYLEN]; // Key is a string
		T Data;               // Client data
		ChHTNode* Next;
		ChHTNode(const T& data) : Data(data), Next(0) {}; // constructor//////////////////////////////////////////////Take out next
	};

	struct ChHTHeadNode   // Each list has a special head pointer
	{
		ChHTNode* Nodes;
		ChHTHeadNode() : Nodes(0), Count(0) {};
		int Count; // For testing
	};

	ChHashTable(const HTConfig& Config, ObjectAllocator* allocator = 0);
	~ChHashTable();
	void insert(const char *Key, const T& Data);  // Insert a key/data pair into table. Throws an exception if the insertion is unsuccesful
	void remove(const char *Key);                 // Delete an item by key. Throws an exception if the key doesn't exist.
	const T& find(const char *Key) const;         // Find and return data by key. Throws an exception if the key doesn't exist
	void clear();								  // Removes all items from the table (Doesn't deallocate table)
	HTStats GetStats() const;                     // Allow the client to peer into the data
	const ChHTHeadNode* GetTable() const;
	void GrowTable();
	ChHashTable(const ChHashTable& rhs) = delete;
	ChHashTable& operator=(const ChHashTable& rhs) = delete;

private:
	HTConfig config_;
	bool created_;
	ChHTHeadNode* table_;
	ChHTHeadNode head_;
	HTStats stats;
};

#include "ChHashTable.cpp"
#endif

