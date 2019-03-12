/******************************************************************************/
/*!
\file   Vector.cpp
\author Lauren Turnbow
\brief  
  This is the implementation file for all member functions
  of a class called Vector, as specified in specification
  file Vector.h.  
  
  Functions include:
    - SubscriptError
    - GetSubscript
    - swap
    - Vector
    - ~Vector
    - push_back
    - push_front
    - operator[]
    - clear
    - empty
    - size
    - capacity
    - allocations
    - pop_back
    - pop_front
    - insert
    - remove
    - operator=
    - operator+=
    - operator+
    - swapv
    - reverse
    - operator==
    - shrink_to_fit
    - check_bounds
    - grow
    - selection_sort
    - bsearch
    
    Hours spend on this assignment: 1

*/
/******************************************************************************/
#include "Vector.h"
#include <iostream>  // cout
#include <cstdlib>   // abort

namespace CS170
{
/******************************************************************************/
/*!
  \brief
     Helper function used to swap to items

  \param a
    One item that will be swapped with another
    
  \param b
    Second item that will be swapped with the other

*/
/******************************************************************************/
  template <typename T>
  void swap(T &a, T& b)
  {
    T temp = a;          // Temporary for first element
    a = b;               // Set first element to second element
    b = temp;            // Set second element to temporary value
  }

/******************************************************************************/
/*!
  \brief
    Constructor

*/
/******************************************************************************/
  Vector::Vector() : array_(0), size_(0), capacity_(0), allocs_(0)
  {
                        // Initialize all private members to zero
  }

/******************************************************************************/
/*!
  \brief
    copy constructor

  \param rhs
    vector to be copied

*/
/******************************************************************************/
  Vector::Vector(const Vector& rhs)
  {
    unsigned size = rhs.size();     // Size of vector passed to function
    
    array_ = new int[size];         // Allocate array to have size of rhs 
    
    for (unsigned int i = 0; i < size; i++)
    {
      array_[i] = rhs[i];           // Copy rhs to private member array
    }
    
    size_ = size;                   // Resetting private data members
    capacity_ = size;
    allocs_ = 1;
  }

/******************************************************************************/
/*!
  \brief
    Constructor that creates a vector out of an array

  \param array
    Array to be copied to the vector
  
  \param size
    Size of array

*/
/******************************************************************************/
  Vector::Vector(const int array[], unsigned size)
  {
    array_ = new int [size];      // Allocate array to have size of rhs
    
    for (unsigned int i = 0; i < size; i++)
    {
      array_[i] = array[i];       // Copy const array to private member array
    }
    
    capacity_ = size;             // Resetting private data members
    size_ = size;
    allocs_ = 1;
  }
/******************************************************************************/
/*!
  \brief
    empties the vector

  \return
    Returns a size of 0 to indicate an empty array

*/
/******************************************************************************/
  bool Vector::empty() const
  {
    return size_ == 0;   // Return true or false if size is equal to 0 or not
  }

/******************************************************************************/
/*!
  \brief
    returns the size

  \return
    returns the size of the array

*/
/******************************************************************************/
  unsigned Vector::size() const
  {
    return size_;     
  }

/******************************************************************************/
/*!
  \brief
    returns the capacity of the array
    
  \return
    returns the capacity of the array

*/
/******************************************************************************/
  unsigned Vector::capacity() const
  {
    return capacity_;
  }

/******************************************************************************/
/*!
  \brief
    returns the number of arrays allocated
    
  \return
    returns the nubmer of arrays allocated

*/
/******************************************************************************/
  unsigned Vector::allocations() const
  {
    return allocs_;
  }

/******************************************************************************/
/*!
  \brief
    Destructor

*/
/******************************************************************************/
  Vector::~Vector()
  {
    clear();                // Clear elements in the array
    delete [] array_;       // Delete the array
  }

/******************************************************************************/
/*!
  \brief
    Clears the array

*/
/******************************************************************************/
  void Vector::clear()
  {
    size_ = 0;                     // Set size to zero to clear elements
    delete [] array_;              // Delete the array
             
    int *temp_array_ = new int[0]; // Allocate temporary array of size 0
       
    array_ = temp_array_;          // Set temp array to array
    capacity_ = 0;  
  }

/******************************************************************************/
/*!
  \brief
    overloads subscript operators for constant variables

  \param index
    index of element of array that is to be returned
    
  \return
    returns value at position in array specified by index

*/
/******************************************************************************/
  int Vector::operator[](unsigned index) const
  {
    check_bounds(index);          // Check if the index is valid
    return this->array_[index];   // Return value at that indicated position
  }

/******************************************************************************/
/*!
  \brief
    overloads subscript operators for non-constant variables

  \param index
    index of element of array that is to be returned
    
  \return
    returns value at position in array specified by index

*/
/******************************************************************************/
  int& Vector::operator[](unsigned index)
  {
    check_bounds(index);         // Check if the index is valid
    return this->array_[index];  // Return value at that indicated position
  }
    
/******************************************************************************/
/*!
  \brief
    Adds element to the end of the array

  \param value
    value of element that is to be added to the array

*/
/******************************************************************************/
  void Vector::push_back (int value)
  {
    if (size_ < capacity_)     // If there is room in the array
      array_[size_] = value;   // Add value to the end
        
    else                       // If there isn't room in the array
    {
      grow();                  // Grow the array
      array_[size_] = value;   // Add value to the end
    }
        
    size_++;                   // Increment the size
  }

/******************************************************************************/
/*!
  \brief
    Adds element to the front of the array

  \param value
    value of element that is to be added to the array

*/
/******************************************************************************/
  void Vector::push_front (int value)
  {
    if (size_ < capacity_)              // If there is room in the array
    {
      for (unsigned int i = size_; i > 0; i--)
        array_[i] = array_[i - 1];      // Move elements up one
                      
      array_[0] = value;                // Set front element to value
    }
        
    else                                // If there isn't room in the array
    {
      grow();                           // Grow the array
      
      for (unsigned int i = size_; i > 0; i--)
        array_[i] = array_[i - 1];      // Move elements up one
                
      array_[0] = value;                // Set front element to value
    }
      
    size_++;                            // Increment size
  }

/******************************************************************************/
/*!
  \brief
    Removes last element

*/
/******************************************************************************/
  void Vector::pop_back()
  {
    if (size_ != 0)            // If array is not empty
      size_--;                 // Decrease the size to delete last element
  }

/******************************************************************************/
/*!
  \brief
    Removes first element

*/
/******************************************************************************/
  void Vector::pop_front()
  {
    if (size_ != 0)                    // If array is not empty
    {
      for (unsigned int i = 0; i < size_ - 1; i++)
        array_[i] = array_[i + 1];     // Move elements up one
      
      size_--;                         // Decrease size
    }
  }

/******************************************************************************/
/*!
  \brief
    Inserts a new node at the specified position

  \param value
    value of element that is to be added to the array
    
  \param position
    position of value to be inserted

*/
/******************************************************************************/
  void Vector::insert(int value, unsigned position)
  {
    check_bounds(position);            // Check if position is valid
    
    if (size_ + 1 > capacity_)         // If there isn't room in the array
    {
      grow();                          // Grow the array
      
      // Move elements up to be able to insert at specified position
      for (unsigned int i = 0, j = 1; size_ - i > position; i++, j++)
        array_[size_ - i] = array_[size_ - j];
      
      array_[position] = value;        // Insert value
      size_++;                         // Increment size
    }
    
    else                               // If there is room in the array
    {
      // Move elements up to be able to insert at specified position
      for (unsigned int i = 0, j = 1; size_ - i > position; i++, j++)
        array_[size_ - i] = array_[size_ - j];
      
      array_[position] = value;        // Insert value
      size_++;                         // Increment size
    }
  }

/******************************************************************************/
/*!
  \brief
    Removes an element with the specified value

  \param value
    value of element that is to be removed from the array

*/
/******************************************************************************/
  void Vector::remove(int value)
  {
    unsigned vecSize = size();       // Size of vector
    int index = NO_INDEX;            // Starting with an invalid index
    
    for (unsigned i = 0; i < vecSize; i++)
    {
      if (array_[i] == value)        // If specified value is found
      {
        index = int(i);              // Set index to that position
        break;
      }
    }
    
    if (index != NO_INDEX)           // If index is valid
    {
      for (unsigned i = unsigned(index); i < vecSize; i++)
        array_[i] = array_[i + 1];   // Move elements back in array
      
      size_--;                       // Decrement size
    } 
  }

/******************************************************************************/
/*!
  \brief
    Assignment operator

  \param rhs
    Vector that will be assigned to implicit object
    
  \return
    Returns a reference to a vector object

*/
/******************************************************************************/
  Vector& Vector::operator=(const Vector& rhs)
  {
    unsigned size = rhs.size();      // Size of vector
    
    if (capacity_ < size)            // If vector is too small
    {
      delete [] array_;              // Delete the array
      array_ = new int [size];       // Reallocate the array 
      capacity_ = size;              // Reset capacity private member
      allocs_++;                     // Increment number of allocations
      
      for (unsigned i = 0; i < size; i++)
        array_[i] = rhs[i];          // Copy passed vector into array
      
      size_ = size;                  // Reset size private member
      return *this;                  // Return implicit object
    }
    
    else                             // If vector is not too small
    {
      for (unsigned i = 0; i < size; i++)
        array_[i] = rhs[i];          // Copy passed vector into array
      
      size_ = size;                  // Reset size private member
      return *this;                  // Return implicit object
    }
  }

/******************************************************************************/
/*!
  \brief
    Concatenates two vectors

  \param rhs
    Vector object that will be concatenated with implicit object
    
  \return
    returns a vector object

*/
/******************************************************************************/
  Vector Vector::operator+(const Vector& rhs) const
  {
    Vector newArray;         // Create new vector object
    newArray += *this;       // Add implicit object to new vector
    newArray += rhs;         // Add passed vector to new vector
    
    return newArray;
  }

/******************************************************************************/
/*!
  \brief
    Concatenates a vector onto the end of this vector

  \param rhs
    vector object that will be concatenated with implicit object
  
  \return
    returns a reference to a vector object

*/
/******************************************************************************/
  Vector& Vector::operator+=(const Vector& rhs)
  {
    unsigned rhsSize = rhs.size();              // Size of vector
    
    for (unsigned i = 0; i < rhsSize; i++)
      push_back(rhs[i]);                        // Add elements to the end
     
    return *this;                               
  }

/******************************************************************************/
/*!
  \brief
    Swaps two vectors

  \param other
    The vector that will be swapped with the this vector

*/
/******************************************************************************/
  void Vector::swapv(Vector &other)
  {
    swap(array_, other.array_);       // Swap elements in the array
    swap(size_, other.size_);         // Swap size members
    swap(capacity_, other.capacity_); // Swap capacity members
    swap(allocs_, other.allocs_);     // Swap allocations
  }

/******************************************************************************/
/*!
  \brief
    Reverses the contents of this vector

*/
/******************************************************************************/
  void Vector::reverse()
  {
    // Temporary value for switching elements in the array
    int temp;          
    
    for (unsigned int i = 0; i < size_ / (unsigned)2; i++)
    {
      temp = array_[i];          // Temp value is equal to element of array  
      // Array at i equals corresponding element at opposite end of array      
      array_[i] = array_[size_ - (i + 1)];
      // Corresponding element at opposite end of array is equal to temp
      array_[size_ - (i + 1)] = temp;
    }
  }

/******************************************************************************/
/*!
  \brief
    Checks to see if two vectors are the same size and all of their contents
    are equal

  \param rhs
    The vector that will be compated to this vector
  
  \return
    Returns true if the vectors are equal and false if they aren't

*/
/******************************************************************************/
  bool Vector::operator==(const Vector& rhs) const
  {
    if (size_ != rhs.size_)     // If sizes aren't equal, return false
      return false;
    
    for (unsigned i = 0; i < size_; i++)
    {
      if (array_[i] == rhs[i]) // If elements are equal continue
        continue;
        
      else
        return false;          // If elements aren't equal vectors aren't equal
    }
    
    return true;               // If end of loop is reached, return true
  }

/******************************************************************************/
/*!
  \brief
    Shrinks the array to have the capacity equal to the size

*/
/******************************************************************************/
  void Vector::shrink_to_fit()
  {
    // If size is already equal to capacity, do nothing
    if (size_ == capacity_)    
      return;
    
    else                   // If capacity is not equal to size
    {
      capacity_ = size_;   // Reduce capacity to fit  
      allocs_++;           // Increment the number of allocations
    }
  }

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
// private 
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*!
  \brief
    Checks to see if the index is out of bounds of the array

  \param index
    Index of array that is to be checked

*/
/******************************************************************************/
  void Vector::check_bounds(unsigned index) const
  {
    if (index >= size_)              // If specified index is out of bounds
    {
      int badSubscript = (int)index; // Set badSupscript to index
      // Throw subscript error with badSupscript
      throw SubscriptError(badSubscript);
    }
  }

/******************************************************************************/
/*!
  \brief
    Creates an array twice the capacity of the original and places values 
    inside of the new array
    
*/
/******************************************************************************/
  void Vector::grow()
  {
    // Double the capacity
    if (capacity_)
      capacity_ *= 2;
    else
      capacity_ = 1;
    
    // Allocate new array with doubled capacity
    int *vector = new int[capacity_];       
       
    for (unsigned int i = 0; i < size_; i++)
      vector[i] = this->array_[i];   // Array is equal to new vector
            
    delete [] array_;                // Delete the array
    array_ = vector;                 // Pointer to array is equal to vector
    allocs_++;                       // Increment allocations
  }
  
/******************************************************************************/
/*!
  \brief
    sorts a vector
    
  \return
    Returns the number of swaps and comparisons

*/
/******************************************************************************/
  Vector::SortResult Vector::selection_sort()
  {
    SortResult sort;       // Struct called sort
    sort.compares = 0;     // Set compares to 0
    sort.swaps = 0;        // Set swaps to 0
    
    for (unsigned i = 0; i < size_; i++)
    {
      unsigned currentPos = 0;    // Set current position to 0
      int temp1 = array_[i];      // Set temp1 to element at array
      int temp2 = 0;              // Set temp2 to zero
      
      for (unsigned j = i + 1; j < size_; j++)
      {
        temp2 = array_[j];        // Set temp2 to element at array
        
        if (temp2 < temp1)        // If temp2 is smaller than temp1
        {
          temp1 = temp2;          // Set temp2 to temp1
          currentPos = j;         // Reset currentPos
        }
        sort.compares++;          // Increment compares
      }
      
      if (temp1 < array_[i])      // If temp1 is less than array 
      {
        swap(array_[i], array_[currentPos]);    // Swap values
        sort.swaps++;                           // Increment swaps
      }
    }
    return sort;                                // Return sort struct
  }

/******************************************************************************/
/*!
  \brief
    Searches a list

  \param value
    Value that will be searched for
    
  \return
    The position of the value if found in the list

*/
/******************************************************************************/
  int Vector::bsearch(int value) const
  {
    int beginPosition = 0;                  // Set beginning Position to 0
    // Set end position to size
    int endPosition = static_cast<int>(size_); 
    // Middle position
    int position = (beginPosition + endPosition) / 2;  
    
    while (beginPosition <= endPosition)    // While beginning is less than end
    {
      if (array_[position] == value)        // If value is found
        return position;                    // Return position
      
      if (array_[position] > value)         // If value is less than
      {
        // Value is in lower portion of array
        endPosition = position - 1;
        // Set new middle value
        position = (beginPosition + endPosition) / 2;
      }
      
      // If value is greater than, it is in higher portion of array
      else
      {
        beginPosition = position + 1;
        // Set new middle value
        position = (beginPosition + endPosition) / 2;
      }
    }
    
    // Return if value was not found
    return CS170::Vector::NO_INDEX;
  }
} // namespace CS170  
