/******************************************************************************/
/*!
\file   vector.h
\author Lauren Turnbow
\brief  
  Header file for SparseVector.cpp
*/
/******************************************************************************/
#include <iostream>
namespace CS225 { 
struct ElementNode {
  int data;
  int pos;
  struct ElementNode *next;
};
class ElementProxy;

class SparseVector {
  public:
    // Print function
    void PrintRaw() const;
    // Default constructor
    SparseVector();
    // Copy constructor
    SparseVector(SparseVector const & obj);
    // Destructor
    ~SparseVector();
    
    // Overloaded operators
    SparseVector& operator=(const SparseVector& obj);
    SparseVector operator+(SparseVector &obj);
    SparseVector operator*(const int multiplier);
    int operator*(const SparseVector& obj) const;
    int operator[](long pos) const;
    ElementProxy operator[](long pos);
    
    // Functions
    int Get(long pos) const;
    void Insert(int val, long pos);
    void Delete(long pos);
    
    // Friend functions
    friend std::ostream& operator<<(std::ostream &out, const SparseVector &v);
    friend SparseVector operator*(const int multiplier2, const SparseVector& obj);
    friend SparseVector operator+(const SparseVector& lhs, const SparseVector& rhs);
  
  private:
    ElementNode* pHead;
    long dimension;
};
 
class ElementProxy {
  public:
    // Constructor
    ElementProxy(SparseVector& v, long pos) : v(v), pos(pos) {}
    // Overloaded operators
    ElementProxy& operator=(const ElementProxy& EP);
    ElementProxy& operator=(long val);
    ElementProxy& operator+=(long val);
    ElementProxy& operator-=(long val);
    operator int() const;

  private:
    SparseVector &v;
    long pos;
};
}