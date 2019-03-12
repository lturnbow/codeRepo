/******************************************************************************/
/*!
\file   BList.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS280
\par    Assignment #2
\date   2/8/2017
*/
/******************************************************************************/
#ifndef BLIST_H
#define BLIST_H
#include <string>     // error strings

class BListException : public std::exception
{
  private:  
    int m_ErrCode;
    std::string m_Description;

  public:
    BListException(int ErrCode, const std::string& Description) :
    m_ErrCode(ErrCode), m_Description(Description) {};

    virtual int code(void) const { 
      return m_ErrCode; 
    }

    virtual const char *what(void) const throw() {
      return m_Description.c_str();
    }

    virtual ~BListException() throw() { }
    enum BLIST_EXCEPTION {E_NO_MEMORY, E_BAD_INDEX, E_DATA_ERROR};
};

struct BListStats
{
  BListStats() : NodeSize(0), NodeCount(0), ArraySize(0), ItemCount(0)  {};
  BListStats(size_t nsize, int ncount, int asize, int count) : 
     NodeSize(nsize), NodeCount(ncount), ArraySize(asize), ItemCount(count)  {};

  size_t NodeSize; // Size of a node
  int NodeCount;   // Number of nodes in the list
  int ArraySize;   // Max number of items in each node
  int ItemCount;   // Number of items in the entire list
};  

template <typename T, int Size = 1>
class BList
{
  public:
    struct BNode
    {
      BNode *next;
      BNode *prev;
      int count; // number of items currently in the node
      T values[Size];
      BNode() : next(0), prev(0), count(0) {}
    };

    BList();							  // default constructor                        
    BList(const BList &rhs);			  // copy constructor
    ~BList();						      // destructor                         
    BList& operator=(const BList &rhs);
    void push_back(const T& value);       // arrays will be unsorted
    void push_front(const T& value);      // arrays will be unsorted
    void insert(const T& value);          // arrays will be sorted
    void remove(int index);
    void remove_by_value(const T& value); 
    int find(const T& value) const;       // returns index, -1 if not found
    T& operator[](int index);             // for l-values
    const T& operator[](int index) const; // for r-values
    size_t size(void) const;              // total number of items (not nodes)
    void clear(void);                     // delete all nodes 
    static size_t nodesize(void);         // so the driver knows the size

    // For debugging
    const BNode *GetHead() const;
    BListStats GetStats() const;

	// Helper functions
	BNode* splitNode(BNode* node, const T value);
	BNode* makeNode();
	void insertFront(BNode* node, const T value);
	void insertMiddle(BNode* node, const T value);
	void insertEnd(BNode* node, const T value);
	void increaseCount(BNode *node);
	void decreaseCount(BNode *node);

  private:
    BNode *head_;           // points to the first node
    BNode *tail_;           // points to the last node
    // Other private members that you need
	BListStats stats;
	bool flag;
};
#include "BList.cpp"
#endif // BLIST_H
