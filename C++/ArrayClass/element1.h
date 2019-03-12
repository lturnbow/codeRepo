/******************************************************************************/
/*!
\file   element1.h
\author Lauren Turnbow
\brief
Declaration of element1 class
*/
/******************************************************************************/
#ifndef ELEMENT1_H
#define ELEMENT1_H
#include <iostream>
#include "abstract-element.h"

namespace CS225 {
  class Element1 : public AbstractElement {
    public:
      Element1(int _val);
      virtual void Print() const;
      virtual int Get() const;
      virtual void Set(int new_val);
      virtual AbstractElement* Clone();
      
    private:
      int val;
  };
}
#endif
