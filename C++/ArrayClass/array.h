/******************************************************************************/
/*!
\file   array.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS225
\par    Assignment #4
\date   11/6/2016
\brief
Declaration of array class
*/
/******************************************************************************/
#ifndef ARRAY_H
#define ARRAY_H
#include "abstract-element.h"
#include "element-factory.h"
#include <iostream>

namespace CS225 {
	class Array {
		public:
			Array(int * array, unsigned int _size, const ElementFactory* _pElementFactory);
			Array(const Array & obj);
			~Array();
			Array& operator=(const Array & obj);
      void Print() const;
			int Get(unsigned int pos) const;
			void Set(int id, int pos, int value);
			
		private:
			AbstractElement** data;
			unsigned int size;
			const ElementFactory* pElementFactory;
			int* refCounter;
	};
}
#endif
