/******************************************************************************/
/*!
\file   vector.cpp
\author Lauren Turnbow
\brief  
  Header file for SparseVector.cpp
*/
/******************************************************************************/
#include "vector.h"
//#include <iostream>

  
/******************************************************************************/
/*!
  \brief
     Copy constructor

  \param obj
     Object to be copied
*/
/******************************************************************************/

namespace CS225 {
///////////////////////////////// Print function
/******************************************************************************/
/*!
  \brief
     Prints vector
*/
/******************************************************************************/
void SparseVector::PrintRaw() const {
  ElementNode* curr = pHead;
  std::cout << "Raw vector: ";
  while (curr) {
    std::cout << "(" << curr->data << ", " << curr->pos << ")";
    curr = curr->next;
  }
  std::cout << std::endl;
}
///////////////////////////////// Default constructor
/******************************************************************************/
/*!
  \brief
     Default constructor
*/
/******************************************************************************/
SparseVector::SparseVector() : pHead(NULL), dimension(0) {}

///////////////////////////////// Copy constructor
/******************************************************************************/
/*!
  \brief
     Copy constructor

  \param obj
     Object to be copied
*/
/******************************************************************************/
SparseVector::SparseVector(SparseVector const & obj) : pHead(NULL), dimension(obj.dimension) 
{
  *this = obj;       // Assign passed object to implicit object
}
///////////////////////////////// Destructor
/******************************************************************************/
/*!
  \brief
     Destructor
*/
/******************************************************************************/
SparseVector::~SparseVector() 
{
  ElementNode* temp = pHead;         
  
  while(pHead) {                      // Walk through the list
    pHead = pHead->next;              // Delete each current node in the list
    delete temp;
    temp = pHead;
  }
}
///////////////////////////////// Assignment operator
/******************************************************************************/
/*!
  \brief
     Assignment operator

  \param obj
     Object to be copied
     
  \return
     Returns a reference to a sparse vector
*/
/******************************************************************************/
SparseVector& SparseVector::operator=(const SparseVector& obj)
{
  if (this == &obj) return *this;        // Self-assignment
  ElementNode * walker = obj.pHead;
  
  while (walker) {                      // Walk through the list
    Insert(walker->data, walker->pos);  // Insert each node from passed object to implicit object
    walker = walker->next; 
  }

  dimension = obj.dimension;            // Set the dimension
  
  return *this; 
} 

////////////////////////////////Plus operator
/******************************************************************************/
/*!
  \brief
     Overloaded plus operator

  \param obj
     Object to be added to implicit object
     
  \return
     SparseVector object
*/
/******************************************************************************/
SparseVector SparseVector::operator+(SparseVector& obj)
{
  SparseVector add = *this;            // Set new object to implicit object
  ElementNode* objNode = obj.pHead;

  while (objNode) {
    // Insert the sum of the implicit object and passed object into the newly created sparse vector object
    add.Insert(Get(objNode->pos) + objNode->data, (objNode->pos));
    objNode = objNode->next;
  }
  return add;
}

/////////////////////////////////Multiplication operator returning a SP object
/******************************************************************************/
/*!
  \brief
     Overloaded * operator

  \param multiplier
     Value to multiplier object nodes with
     
  \return 
     SparseVector object
*/
/******************************************************************************/
SparseVector SparseVector::operator*(const int multiplier)
{  
  ElementNode* head = pHead;
  SparseVector mult;
  
  while (head) {
    // Insert the product of the implicit object and passed object into the newly created sparse vector object
    int product = multiplier * Get(head->pos);
    mult.Insert(product, head->pos);
    head = head->next;
  }
  return mult;
}

/////////////////////////////////Multiplication opeator returning an int
/******************************************************************************/
/*!
  \brief
     Overloaded * operator returning a scalar product

  \param obj
     Object to be multiplied with
     
  \return
     Return scalar product of two vectors
*/
/******************************************************************************/
int SparseVector::operator*(const SparseVector& obj) const
{
  int total = 0;          
  ElementNode* lhs = pHead;
  ElementNode* rhs = obj.pHead;
  

  while (lhs && rhs) {
    // If the positions are equal add the sum of the nodes to the total
    if (rhs->pos == lhs->pos) {   
      total += rhs->data * lhs->data;   
      lhs = lhs->next;                         
      rhs = rhs->next;
      continue;
    }
    
    // If the positions are not equal and the lhs position is less than the
    // rhs position, move the lhs position up
    else if (lhs->pos < rhs->pos) {     
      lhs = lhs->next;                         
      continue;
    }
    
    // If the positions are not equal and the rhs position is less than the 
    // lhs position, move the rhs position up
    else if (lhs->pos > rhs->pos) {    
      rhs = rhs->next;                        
      continue;
    }
  }
  
  return total;
}
///////////////////////////////////Subscript operator returning an int
/******************************************************************************/
/*!
  \brief
     Overloaded subscript operator

  \param pos
     Position to be returned of the vector
  
  \return
     Return int at position
*/
/******************************************************************************/
int SparseVector::operator[](long pos) const
{
  long position = Get(pos);     // Return the data at the specified position
  return position;
} 
///////////////////////////////////Subscript operator returning an ElementProxy
/******************************************************************************/
/*!
  \brief
     Overloaded subscript operator

  \param pos
     Position to be returned of the vector
     
  \return
     Returns an elementProxy
*/
/******************************************************************************/
ElementProxy SparseVector::operator[](long pos)
{
  return ElementProxy(*this, pos);
}
///////////////////////////////////Get
/******************************************************************************/
/*!
  \brief
     Returns element at a specified position

  \param pos
     Positon of element being searched for
   
  \return
     Returns the int at the specified position
*/
/******************************************************************************/
int SparseVector::Get(long pos) const
{
  ElementNode* walker = pHead;
  
  while (walker) {                // Walk through the list
    if (walker->pos == pos)       // If the position is found
      return walker->data;        // Return data at the position
    walker = walker->next;
  }
  return 0;                       // Return 0 is the position is not found
}

//////////////////////////////////Insert
/******************************************************************************/
/*!
  \brief
     Inserts data at the specified position

  \param val
     Data to be inserted
     
  \param pos
     Position to be inserted at
*/
/******************************************************************************/
void SparseVector::Insert(int val, long pos) 
{
  if (val == 0) {                   // If the value equals 0 don't insert
    Delete(pos); 
    return; 
  }
  
  if (pos >= dimension)
    dimension = pos + 1; 
    
  ElementNode* newNode = new ElementNode;
  ElementNode* walker = pHead;
   
  newNode->data = val;        
  newNode->pos = pos; 

  if (pHead == NULL) {              // If list is null insert directly    
    pHead = newNode;           
    newNode->next = NULL;
    return;
  }               
    
  if (pHead->pos > pos) {          // If position to be inserted is at the front of the list
    newNode->next = pHead;
    pHead = newNode;     
    return;
  }  

  while(walker) {                 // Walk through the list      
    if (walker->pos == pos) {     // If the position to be inserted at is found
      walker->data = val;             
      delete newNode;        
      break;
    }
      
    else if (walker->next == NULL) {     // If position is at end of list
      walker->next = newNode;        
      newNode->next = NULL;   
      break;                
    }
      
    // If position is supposed to be between two nodes that are next to each other
    else if (walker->pos < pos && walker->next->pos > pos) {
      newNode->next = walker->next;
      walker->next = newNode;
      break;
    }

    walker = walker->next;     
  }
  return;
}
//////////////////////////////////Delete
/******************************************************************************/
/*!
  \brief
     Deletes node at position

  \param pos
     Position to delete object at
*/
/******************************************************************************/
void SparseVector::Delete(long pos)
{        
  ElementNode * temp = pHead;   
  ElementNode * walker = pHead;
    
  if (pHead == NULL)           // If there is nothing there to be deleted
    return;
       
  if (pos == 0) {              // If position is at the beginning of the list
    temp = pHead->next;
    delete pHead;
    pHead = temp;
    return;
  }

  if (pos == 1) {              // If the position is the second element in the list
    temp = pHead->next;
    delete pHead;
    pHead = temp;
    return;
  }    
      
  if (pHead->pos == pos) {     // If the position is at the beginning of the list but is not 0
    temp = pHead->next;
    delete pHead;
    pHead = temp;
    return;
  }
  
  while (walker) { 
    if (walker->next == NULL)  // Break if at the end of the list 
      break;
      
    else if (walker->next->pos == pos) {  // If position is found at the next node
      temp = (walker)->next;                     
      walker->next = temp->next;  
      delete temp;
      break;
    } 
      
    walker = walker->next;
  }
  return;
}

//////////////////////////////////friend operator<<
/******************************************************************************/
/*!
  \brief
     Overloaded ostream operator

  \param out
     Reference to an ostream object
     
  \param v
     Object to be used
     
  \return
     Reference to an ostream object
*/
/******************************************************************************/
std::ostream& operator<<(std::ostream &out, const SparseVector &v) 
{
	int i, last_pos =- 1; 
	ElementNode* pHead = v.pHead; 
	while (pHead) { 
		for (i = last_pos + 1; i < pHead->pos; ++i) out << " " << "0"; 
		out << " " << pHead->data; 
		last_pos = pHead->pos; 
		pHead = pHead->next; 
	} 
	for (i = last_pos + 1; i < v.dimension; ++i) out << " " << "0"; 

	return out; 
}
//////////////////////////////////friend operator*
/******************************************************************************/
/*!
  \brief
     Overloaded * operator

  \param multiplier2
     Value to multiply nodes with
     
  \param obj
     Object to be multiplied with
     
  \return
     Returns SparseVector object
*/
/******************************************************************************/
SparseVector operator*(const int multiplier2, const SparseVector& obj)
{
  SparseVector mult;
  ElementNode* objWalker = obj.pHead;
  
  while (objWalker)                      // Walk through list
  {
    // Product of the int and the data of the node at the current position
    int product = multiplier2 * obj.Get(objWalker->pos);
    // Insert the product into the newly created sparse vector object
    mult.Insert(product, objWalker->pos);
    objWalker = objWalker->next;
  }
  return mult;
}

//////////////////////////////////friend operator+
/******************************************************************************/
/*!
  \brief
     Overloaded + operator

  \param lhs
     First object to be added
     
  \param rhs
     Second object to be added
     
  \return
     New added sparseVector
*/
/******************************************************************************/
SparseVector operator+(const SparseVector& lhs, const SparseVector& rhs)
{
  SparseVector add = lhs;
  ElementNode* rhsWalker = rhs.pHead;
  
  while (rhsWalker)
  {
    // Insert the sum of the two nodes of the passed objects
    add.Insert(lhs.Get(rhsWalker->pos) + rhsWalker->data, rhsWalker->pos);
    rhsWalker = rhsWalker->next;
  }
  return add;
}

/*******************************ElementProxy****************************/
/******************************************************************************/
/*!
  \brief
     Overloaded assignment operator

  \param EP
     Element to be set equal to implicit object
     
  \return
     Reference to an ElementProxy
*/
/******************************************************************************/
ElementProxy& ElementProxy::operator=(const ElementProxy& EP)
{
  // Setting element proxy to the EP at the position
  v.Insert(EP.v.Get(EP.pos), pos);
  return *this;
}
/******************************************************************************/
/*!
  \brief
     Overloaded = operator taking a long

  \param val
     Value that will be set to the nodes of the ElementProxy object
     
  \return
     Reference to an element proxy
*/
/******************************************************************************/
ElementProxy& ElementProxy::operator=(long val)
{
  // Inserting the val at the current position
  v.Insert(val, pos);
  return *this;
}
/******************************************************************************/
/*!
  \brief
     Overloaded int operator

  \return
     Returns an int
*/
/******************************************************************************/
ElementProxy::operator int() const
{
  // Returning the data at the current position
  int data = v.Get(pos);
  return data;
}
/******************************************************************************/
/*!
  \brief
     Overloaded += operator

  \param val
     Value to be added to node
  
  \return
     Reference to an ElementProxy object
*/
/******************************************************************************/
ElementProxy& ElementProxy::operator+=(long val)
{
  // Adding to the element proxy
  v.Insert(val + v.Get(pos), pos);
  return *this;
}
/******************************************************************************/
/*!
  \brief
     Overloaded -= operator

  \param val
     Value to be subtracted from node
  
  \return
     Reference to an ElementProxy object
*/
/******************************************************************************/
ElementProxy& ElementProxy::operator-=(long val)
{
  // Subtracting from the element proxy
  v.Insert(v.Get(pos) - val, pos);
  return *this;
}
}



