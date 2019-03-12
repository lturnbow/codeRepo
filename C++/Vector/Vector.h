/******************************************************************************/
/*!
\file   Vector.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS170
\par    MegaLab Assignment
\date   4/6/2016

*/
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef VECTOR_H
#define VECTOR_H
////////////////////////////////////////////////////////////////////////////////

namespace CS170
{

class SubscriptError
{
  public:
    SubscriptError(int Subscript) : subscript_(Subscript) {};
    int GetSubscript() const { return subscript_; }

  private:
    int subscript_;
};

class Vector
{
  public:

    static const int NO_INDEX = -1;
    
    struct SortResult
    {
      unsigned compares; // The number of comparisons done during the sort.
      unsigned swaps;    // The number of swaps done during the sort.
    };

      // Default constructor
    Vector();

      // Destructor
    ~Vector();

      // Adds an element to the back of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items.
    void push_back(int value);

      // Adds an element to the front of the array. If there is
      // not enough room in the array, it will be grown to
      // handle more items. All items to the right must be
      // shifted over one element to the right.
    void push_front(int value);

      // Subscript operators for const and non-const
    int operator[](unsigned index) const;
    int& operator[](unsigned index);

      // Deletes the underlying array and sets size_ to 0
    void clear();

      // Return true if the vector is empty, otherwise, false
    bool empty() const;

      // Returns the number of elements in the vector.
    unsigned size() const;

      // Returns the size of the underlying array
    unsigned capacity() const;

      // The number of memory allocations that have occurred
    unsigned allocations() const;

      // Copy constructor
    Vector(const Vector& rhs);

      // Constructor to create a Vector from an array
    Vector(const int array[], unsigned size);

      // Removes the last element. Does nothing if empty.
    void pop_back();

      // Removes the first element. Does nothing if empty.
    void pop_front();

      // Inserts a new node at the specified position. Now throws an
      // exception if the position is invalid. (Calls check_bounds 
      // which is the function that is actually throwing.)
    void insert(int value, unsigned position);

      // Removes an element with the specified value (first occurrence)
    void remove(int value);

      // Assignment operator
    Vector& operator=(const Vector& rhs);

      // Concatenates a vector onto the end of this vector.
    Vector& operator+=(const Vector& rhs);

      // Concatenates two Vectors.
    Vector operator+(const Vector& rhs) const;

      // Reverses the order of the elements (Linear time)
    void reverse();

      // Swaps the contents of other with this Vector (Constant time)
    void swapv(Vector &other);

      // Equality operator (Linear time)
      // Both vectors must be the same size.
    bool operator==(const Vector& rhs) const;

      // Reallocates an array to match the size of the number
      // of elements. If size == capacity, does nothing.
    void shrink_to_fit();
    
    // Sorts the elements using a selection sort. 
    // Returns the number of swaps/comparisons that occurred.
    SortResult selection_sort();

    // This searches the vector using a binary search instead
    // of a linear search. The data must be sorted. Returns
    // the index. If not found, returns CS170::Vector::NO_INDEX.
    // DO NOT SORT THE DATA IN THIS FUNCTION!!
    int bsearch(int value) const;

  private:
    int *array_;        // The dynamically allocated array
    unsigned size_;     // The number of elements in the array
    unsigned capacity_; // The allocated size of the array
    unsigned allocs_;   // Number of allocations (resizes)

    // Private methods...
    void check_bounds(unsigned index) const;
    void grow();
    
    // Other private methods...
};

} // namespace CS170

#endif // VECTOR_H
