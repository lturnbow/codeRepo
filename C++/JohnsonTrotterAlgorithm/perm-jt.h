/******************************************************************************/
/*!
\file   perm-jt.h
\author Lauren Turnbow
*/
/******************************************************************************/
#ifndef PERM_JOHNSON_TROTTER_H
#define PERM_JOHNSON_TROTTER_H
#include <vector>

class PermJohnsonTrotter 
{	
	public:
		PermJohnsonTrotter(int size);
		bool Next();
		std::vector<int> const& Get() const;
		static int count;
		void Print();
		int factorial(int num);
		
	private:
		std::vector<signed int> dir;
		std::vector<int> element;
		std::vector<std::vector<int> > permutations;
		int Size;
		int numPerm;	
};
#endif
