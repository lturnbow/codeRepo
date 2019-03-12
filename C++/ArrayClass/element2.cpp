/******************************************************************************/
/*!
\file   element2.cpp
\author Lauren Turnbow
\brief
Implementation of element2 class
*/
/******************************************************************************/
#include "element2.h"
namespace CS225 {
/******************************************************************************/
/*!
	\brief
		Element2 constructor

	\param _val
		Value to be set
*/
/******************************************************************************/
	Element2::Element2(int _val) : p_val(new int(_val)) { }

/******************************************************************************/
/*!
	\brief
		Copy constructor

	\param rhs
		Const Element2 object
*/
/******************************************************************************/
	Element2::Element2(const Element2& rhs) : AbstractElement(), p_val(new int(*rhs.p_val)) { }

/******************************************************************************/
/*!
	\brief
		Assignment operator

	\param rhs
		Const object to be assigned

	\return
		Returns reference to Element2
*/
/******************************************************************************/
	Element2& Element2::operator=(const Element2& rhs) 	{
		if (this != &rhs) {
			delete p_val;
			p_val = new int(*rhs.p_val);
		}
		return *this;
	}

/******************************************************************************/
/*!
	\brief
		Get function

	\return
		Returns a value
*/
/******************************************************************************/
	int Element2::Get() const {
		return *p_val;
	}

/******************************************************************************/
/*!
	\brief
		Print function
*/
/******************************************************************************/
	void Element2::Print() const {
		std::cout << "(" << *p_val << ") ";
	}

/******************************************************************************/
/*!
	\brief
		Set function

	\param new_val
		Value to be set
*/
/******************************************************************************/
	void Element2::Set(int new_val) {
		*p_val = new_val;
	}

/******************************************************************************/
/*!
	\brief
		Element2 destructor
*/
/******************************************************************************/
	Element2::~Element2() {
		delete p_val;
	}

/******************************************************************************/
/*!
	\brief
		Clone function

	\return
		Returns an abstract element with with p_val
*/
/******************************************************************************/
	Element2::AbstractElement* Element2::Clone()
	{
		return new Element2(*p_val);
	}
}
