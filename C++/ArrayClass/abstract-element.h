/******************************************************************************/
/*!
\file   abstract-element.h
\author Lauren Turnbow
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
