/******************************************************************************/
/*!
\file   List.cpp
\author Lauren Turnbow
\brief  
  This file implements functions that are used to manipulate a singly-linked 
  list use template types
  
  Functions include:
    - List
    - ~List
    - push_front
    - push_back
    - pop_front
    - front
    - size
    - empty
    - clear
    - operator=
    - operator+=
    - operator+
    - operator[]
    - operator<<
    - list_count
    - node_count
    - new_node
    
    Hours spent on assignment: 1

*/
/******************************************************************************/
namespace CS170
{
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// static members

  template <typename T>
  int List<T>::Node::nodes_alive = 0;   // Number of nodes alive

/******************************************************************************/
/*!

  \brief
    Returns the number of nodes alive
      
  \return 
    Returns the number of nodes alive

*/
/******************************************************************************/
  template <typename T>
  int List<T>::node_count(void)
  {
    return Node::nodes_alive;
  }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// List::Node methods
/******************************************************************************/
/*!

  \brief
    Node constructor. Increments number of nodes alive
    
  \param value
    Value that will be placed in the node

*/
/******************************************************************************/
  template <typename T>
  List<T>::Node::Node(T value) : data(value)
  {
    nodes_alive++;
  }

/******************************************************************************/
/*!

  \brief
    Node destructor. Decrements number of nodes alive

*/
/******************************************************************************/
  template <typename T>
  List<T>::Node::~Node()
  {
    nodes_alive--;
  }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// public methods
/******************************************************************************/
/*!

  \brief
    Default constructor

*/
/******************************************************************************/
  template <typename T>
  List<T>::List()
  {
    head_ = NULL;     // Set the head of the list to NULL
    tail_ = NULL;     // Set the tail of the list to NULL
    size_ = 0;        // Set the size of the list to 0
  }

/******************************************************************************/
/*!
         
  \brief
    Copy constructor
 
  \param list
    List that will be copied  

*/
/******************************************************************************/
  template <typename T>
  List<T>::List(const List & list)
  {
    Node *secondList = list.head_;     // Pointer to list that is being passed
      
    head_ = NULL;                      // Set head to NULL
    tail_ = NULL;                      // Set tail to NULL
      
    while (secondList)                 // While there are nodes in the list
    {
      // Add node to the end of the list with the specified data
      push_back(secondList->data);      
      secondList = secondList->next;   // Move through the list
    }
      
    size_ = list.size();               // Set the size of the list
  }

/******************************************************************************/
/*!
         
  \brief
    List non-default constructor, given an array and size
 
  \param array
    An templated type array that will be placed into the nodes of the 
    singly linked list  
    
  \param size
    The size of the array

*/
/******************************************************************************/
  template <typename T>
  List<T>::List(const T *array, int size)
  {
    // Set head and tail to NULL
    head_ = NULL;
    tail_ = NULL;
      
    // Initialize each node in list to each successive element in the array
    for (int i = 0; i < size; i++)
      push_back(array[i]);
      
    size_ = size;         // Set the size of the list
  }

/******************************************************************************/
/*!
         
  \brief
    List destructor 

*/
/******************************************************************************/
  template <typename T>
  List<T>::~List()
  {
    clear();             // Clear the nodes from the list
  }

/******************************************************************************/
/*!
         
  \brief
    Returns the first item in the list

  \return
    Returns the first item in the list of type T

*/
/******************************************************************************/
  template <typename T>
  T List<T>::front() const         
  {
    return head_->data;
  }

/******************************************************************************/
/*!
         
  \brief
    Returns the number of items in the list
 
  \return
    Returns the number of items in the list

*/
/******************************************************************************/
  template <typename T>
  int List<T>::size() const       
  {
     return size_; 
  }

/******************************************************************************/
/*!
         
  \brief
    Determines if the list is empty or not
 
  \return
    Returns if the list is empty or not  

*/
/******************************************************************************/
  template <typename T>
  bool List<T>::empty() const       
  {
    if (head_ == NULL)              // Is empty if the head is NULL
      return true;
    else
      return false; 
  }

/******************************************************************************/
/*!
         
  \brief
    Adds item to the front of the list
 
  \param Value
    Value that will be placed in the node  

*/
/******************************************************************************/
  template <typename T>
  void List<T>::push_front(const T& Value) 
  {
    Node *frontNode = new_node(Value);  // Create a node with a specified value
    bool isEmpty = empty();             // Set to true if list is empty
      
    if (isEmpty)                        // If there is nothing in the list
    {
      // The head and the tail are both the same node
      head_ = frontNode;
      tail_ = frontNode;
      size_++;                          // Increment the size of the list
    }
      
    else
    {
      frontNode->next = head_;          // Set current head to second element
      head_ = frontNode;                // Set created node to head
      size_++;                          // Increment the size of the list
    }
  }

/******************************************************************************/
/*!
         
  \brief
    Adds item to the end of the list
 
  \param Value
    Value that will be placed in the node  

*/
/******************************************************************************/
  template <typename T>
  void List<T>::push_back(const T& Value) 
  {
    Node *endNode = new_node(Value);   // Create a node with a specified value
    bool isEmpty = empty();            // Set to true if list is empty
        
    if (isEmpty)                       // If there is nothing in the list
    {
      // The head and the tail are both the same node
      head_ = endNode;
      tail_ = endNode;
      size_++;                         // Increment the size of the list
    }
      
    else
    {
      tail_->next = endNode;           // Add created node to end of list
      tail_ = endNode;                 // Set created node to tail
      size_++;                         // Increment the size of the list
    }     
  }

/******************************************************************************/
/*!
         
  \brief
    Removes the first item in the list  

*/
/******************************************************************************/
  template <typename T>
  void List<T>::pop_front()               
  {
    bool isEmpty = empty();         // Set to true if list is empty
      
    if (!isEmpty)                   // If there are nodes in the list
    {
      Node *list = head_;           // Implicit object list
      Node *temp = list->next;      // Temp that keeps tracks of the next node
          
      delete list;                  // Removes the first node in the list
         
      head_ = temp;                 // Set head to next value
      size_--;                      // Decrement size of the list
    }
  }

/******************************************************************************/
/*!
         
  \brief
    Clears the list by removing all nodes 

*/
/******************************************************************************/
  template <typename T>
  void List<T>::clear()
  {
    while (!empty())
      pop_front();
  }

/******************************************************************************/
/*!
         
  \brief
    Returns the value at a certain position in the list
 
  \param index
    The index of the position of the list that will be returned

  \return 
    Returns a reference to the templated type

*/
/******************************************************************************/
  template <typename T>
  const T& List<T>::operator[](int index) const
  {
    Node *list = head_;              // Implicit object set to head
      
    // Move through the list until the specified position
    for (int i = 0; i < index; i++)  
      list = list->next;
      
    return list->data;               // Return value at that position
  }

/******************************************************************************/
/*!
         
  \brief
    Returns the value at a certain position in the list
 
  \param index
    The index of the position of the list that will be returned

  \return 
    Returns a reference to the templated type

*/
/******************************************************************************/
  template <typename T>
  T& List<T>::operator[](int index)
  {
    Node *list = head_;              // Implicit object set to head
      
    // Move through the list until the specified position
    for (int i = 0; i < index; i++)  
      list = list->next;
      
    return list->data;               // Return value at that position
  }

/******************************************************************************/
/*!
         
  \brief
    Sets two lists equal to each other
 
  \param list
    List that will be set equal to

  \return 
    Returns a reference to a list of templated types

*/
/******************************************************************************/
  template <typename T>
  List<T>& List<T>::operator=(const List &list)
  {
    Node *rhsList = list.head_;           // Create a node with specified value
    
    if (this == &list)
      return *this;
      
    // Add nodes to end of lis until the size of the list
    for (int i = 0; i < list.size_; i++)
    {
      T value = rhsList->data;         // Current value of list
        
      push_back(value);              
      rhsList = rhsList->next;           // Move through the list
    }
     
    return *this;
  }

/******************************************************************************/
/*!
         
  \brief
    Concatenates two lists
 
  \param list
    List that will be set concatenated with the implicit object

  \return 
    Returns a list

*/
/******************************************************************************/
  template <typename T>
  List<T> List<T>::operator+(const List &list) const
  {
    List concatList(*this);      // List object that will be added to
    Node *rhsList = list.head_;   // Create a node with specified value       
    
    for (int i = 0; i < size_; i++)
    {
      T value = rhsList->data;    // Current value of node
          
      concatList.push_back(value);  // Add value to end of list
      rhsList = rhsList->next;      // Move through the list
    }
      
    return concatList;
  }

/******************************************************************************/
/*!
         
  \brief
    Concatenates two lists
 
  \param list
    List that will be set concatenated with the implicit object

  \return 
    Returns a list

*/
/******************************************************************************/
  template <typename T>
  List<T>& List<T>::operator+=(const List &list)
  {
    Node *rhsList = list.head_;          // Create a node with specified value  
      
    // Add nodes to list until the size of the list
    for (int i = 0; i < list.size_; i++)
    {
      T value = rhsList->data;        // Current value of list
       
      push_back(value);                
      rhsList = rhsList->next;          // Move through the list          
    }
        
    return *this;
  }

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// private methods
/******************************************************************************/
/*!
         
  \brief
    Creates a node
 
  \param data
    Data that will be placed in the node

  \return 
    Returns a node

*/
/******************************************************************************/
  template <typename T>
  typename List<T>::Node *List<T>::new_node(const T& data) const
  {
    Node *node = new Node(data); // create the node
    node->next = 0;              // no next pointer yet
    return node;
  }

} // namespace CS170

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
// non-members

#include <iomanip>

/******************************************************************************/
/*!
         
  \brief
    Outputs node data and next node
 
  \param os
    The output streambuf
    
  \param list
    The list that will be outputted

  \return 
    Returns the output stream

*/
/******************************************************************************/
template <typename T>
std::ostream &CS170::operator<<(std::ostream & os, const CS170::List<T> &list)
{
    // Start at the top
  typename CS170::List<T>::Node *pnode = list.head_;

    // Print each item
  while (pnode != 0)
  {
    os << std::setw(4) << pnode->data;
    pnode = pnode->next;
  }
  os << std::endl;
  return os;
}

