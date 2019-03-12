/******************************************************************************/
/*!
\file   array.cpp
\author Lauren Turnbow
\brief
This file implements functions of the array class
*/
/******************************************************************************/
#include "array.h"

namespace CS225 {
/******************************************************************************/
/*!
	\brief
		Copy constructor

	\param obj
		Const object to be copied
*/
/******************************************************************************/
	Array::Array(Array const & obj) : data(obj.data), size(obj.size), pElementFactory(obj.pElementFactory), refCounter(obj.refCounter)
	{
		// Initialize all private members
		*refCounter += 1;    // Increment counter after copying
	}

/******************************************************************************/
/*!
	\brief
		Non default constructor

	\param array
		Array to be put into data

	\param _size
		Size of array

	\param _pElementFactory
		Element factory to be used
*/
/******************************************************************************/
	Array::Array(int * array, unsigned int _size, const ElementFactory* _pElementFactory) :
		data(new AbstractElement*[_size]), size(_size), pElementFactory(_pElementFactory), refCounter(new int)
	{
		*refCounter = 1;

		for (unsigned int i = 0; i < size; ++i)
			data[i] = pElementFactory->MakeElement(1, array[i]);
	}

/******************************************************************************/
/*!
	\brief
		Assignnment operator

	\param obj
		Const object to be assigned
*/
/******************************************************************************/
	Array& Array::operator=(const Array & obj)
	{
    pElementFactory = obj.pElementFactory;
    
		if (*refCounter == 1)                     // If only one object is sharing the array
		{
			for (unsigned int i = 0; i < size; i++) // Delete old object
				delete data[i];
			delete[] data;
			delete refCounter;
		}

		else if (*refCounter != 1)    // If more than one object is sharing the array
    // Decrement counter of implicit object because it will no longer have implicit object looking at it
			*refCounter -= 1;           
    
    data = obj.data;             // Assign private variables to private variables of passed object
		size = obj.size;
    refCounter = obj.refCounter; // Switch reference counter pointers
    *refCounter += 1;            // Increment counter of passed object
		return *this;
	}

/******************************************************************************/
/*!
	\brief
		Get function

	\param pos
		Position to be found

	\return
		Returns value at position
*/
/******************************************************************************/
	int Array::Get(unsigned int pos) const
	{
		return data[pos]->Get();
	}

/******************************************************************************/
/*!
	\brief
		Set function

	\param id
		id of element

	\param pos
		Position to be deleted

	\param value
		New value
*/
/******************************************************************************/
	void Array::Set(int id, int pos, int value)
	{
		if (*refCounter != 1)                               // If more than one object is sharing the array
		{
			// Create a new AbstractElement object, using virtual constructor. Size of implicit object array
			AbstractElement** clone = new AbstractElement*[size];
			// Setting clone array equal to clone of implicit data array
			for (unsigned int i = 0; i < size; i++)
				clone[i] = data[i]->Clone();

			*refCounter -= 1;              // Decrement counter of implicit object
			refCounter = new int;          // Creating new reference counter for clone array
			*refCounter = 1;               // Set reference counter equal to one because only implicit object is looking at clone array

			data = clone;                  // Set implicit data pointer to clone pointer
		}
    
    delete data[pos];               // Delete value at old poisition and assign new value
		data[pos] = pElementFactory->MakeElement(id, value);
	}

/******************************************************************************/
/*!
	\brief
		Print function
*/
/******************************************************************************/
	void Array::Print() const
	{
		for (unsigned int i = 0; i < size; ++i)
			data[i]->Print();
		std::cout << std::endl;
	}
  
/******************************************************************************/
/*!
	\brief
		Destructor
*/
/******************************************************************************/
	Array::~Array()
	{
		if (*refCounter > 1)          // If more than one object is sharing the array, decrement counter
			*refCounter -= 1;

		else if (*refCounter == 1)    // If only one object is sharing the array, delete data array and reference counter
		{
			for (unsigned int i = 0; i < size; i++)
				delete data[i];
			delete[] data;
			delete refCounter;
		}
	}
}
