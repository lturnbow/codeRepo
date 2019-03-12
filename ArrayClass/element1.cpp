/******************************************************************************/
/*!
\file   element1.cpp
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS225
\par    Assignment #4
\date   11/6/2016
\brief
Implementation of element1 class
*/
/******************************************************************************/
#include "element1.h"
namespace CS225 {
/******************************************************************************/
/*!
	\brief
		Element1 constructor

	\param _val
		Value to be placed in element1
*/
/******************************************************************************/
	Element1::Element1(int _val) : val(_val) { }

/******************************************************************************/
/*!
	\brief
		Element1 get function

	\return
		Value
*/
/******************************************************************************/
	int Element1::Get() const
	{
		return val;
	}

/******************************************************************************/
/*!
	\brief
		Set function

	\param new_val
		Set new value
*/
/******************************************************************************/
	void Element1::Set(int new_val)
	{
		val = new_val;
	}

/******************************************************************************/
/*!
	\brief
		Print function
*/
/******************************************************************************/
	void Element1::Print() const
	{
		std::cout << "[" << Get() << "] ";
	}

/******************************************************************************/
/*!
	\brief
		Clone function

	\return
		Returns an AbstractElement
*/
/******************************************************************************/
	Element1::AbstractElement* Element1::Clone()
	{
		return new Element1(val);
	}
}
