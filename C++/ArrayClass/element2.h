/******************************************************************************/
/*!
\file   element2.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS225
\par    Assignment #4
\date   11/6/2016
\brief
Declaration of element2 class
*/
/******************************************************************************/
#ifndef ELEMENT2_H
#define ELEMENT2_H
#include <iostream>
#include "abstract-element.h"

namespace CS225 {

  class Element2 : public AbstractElement {
    public:
      Element2(int _val);
      Element2(const Element2& rhs);
      Element2& operator=(const Element2& rhs);
      virtual int Get() const;
      virtual void Set(int new_val);
      virtual void Print() const;
      virtual ~Element2();
      virtual AbstractElement* Clone();
      
    private:
      int * p_val;
  };

}
#endif
