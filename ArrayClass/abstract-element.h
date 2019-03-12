/******************************************************************************/
/*!
\file   abstract-element.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS225
\par    Assignment #4
\date   11/6/2016
\brief
Declaration of AbstractElement class
*/
/******************************************************************************/
#ifndef ABSTRACT_ELEMENT
#define ABSTRACT_ELEMENT
#include "CRTP.h"
namespace CS225 {
	class AbstractElement : public ObjectCounter<AbstractElement>
	{
    public:
      AbstractElement() {}
      virtual ~AbstractElement() {}
      virtual int Get() const = 0;
      virtual void Print() const = 0;
      virtual void Set(int newVal) = 0;
      virtual AbstractElement* Clone() = 0;
	};
}
#endif
