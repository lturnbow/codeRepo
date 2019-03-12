/******************************************************************************/
/*!
\file   perm-jt.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include "perm-jt.h"
#include <iostream>

int PermJohnsonTrotter::count = 0; // Initializing static count function for 
								   // the print function

/******************************************************************************/
/*!
	\brief
		Constructor for Johnson Trotter permutation
	\param size
		Amount of numbers to compute the permutations of
*/
/******************************************************************************/
PermJohnsonTrotter::PermJohnsonTrotter(int size) : dir(0, -1), element(0, 0), 
				 permutations(0, element), Size(size), numPerm( factorial(size))
{
	bool noMorePerm = false;
	
	// Initializes vector with number and directions
	for (int i = 0; i < size; i++) 
	{
		dir.push_back(-1);           // Start with directions pointing left
		element.push_back(i + 1);    // Start with number 1 through size
	}
	
	permutations.push_back(element); // Push back initial permutation
	while (!noMorePerm)
	{
		signed int max = -1;         // Values to find the max mobile element
		signed int oldMaxI = -1;

		// Finding the largest mobile element
		for (int i = 0; i < size; i++)
		{
			// If the element points left and it is at the beginning of the list
			// so it's pointing to nothing, continue
			if (i == 0 && dir[i] == -1) continue;
			// If element point right and is at the end of the list, so it 
			// points to nothing, continue
			else if (i == size - 1 && dir[i] == 1) continue;
			
			else
			{
				// If element has left mobility, check if it is larger than the
				// element it's pointing to and if it's bigger than max, update
				// the max and the index
				if (dir[i] == -1)
				{
					if (element[i - 1] < element[i] && max < element[i])
					{
						oldMaxI = i;
						max = element[i];
					}
				}
				
				// If element has right mobility, check if it's larger than the
				// element it's pointing to and it's bigger than max, update the
				// max and the index
				else if (dir[i] == 1 && 
						 element[i + 1] < element[i] && max < element[i])
				{
					oldMaxI = i;
					max = element[i];
				}
			}
		}

		// If there was never a number that was mobile, end the function
		if (max == -1 || oldMaxI == -1)
		{
			noMorePerm = true;
			return;
		}

		// If the element had left mobility, swap the element with the one that 
		// it's pointing at in the element and direction vectors
		if (dir[oldMaxI] == -1)
		{
			std::swap(element[oldMaxI], element[oldMaxI - 1]);
			std::swap(dir[oldMaxI], dir[oldMaxI - 1]);
		}
		
		// If the element had right mobility, swap the element with the one that
		// it's pointing at in the element and direction vectors
		else if (dir[oldMaxI] == 1)
		{
			std::swap(element[oldMaxI], element[oldMaxI + 1]);
			std::swap(dir[oldMaxI], dir[oldMaxI  + 1]);
		}

		// Go through the list and reverse the direction of any element that is
		// larger than the max
		for (int i = 0; i < size; i++)
		{
			if (element[i] > max)
			{
				if (dir[i] == -1)
					dir[i] = 1;
				else
					dir[i] = -1;
			}
		}

		// Push back the current calculated permutation
		permutations.push_back(element);
	}
}

/******************************************************************************/
/*!
	\brief
		Computes the factorial of a given number
	\param num
		Number to compute factorial of
	\return
		Returns factorial
*/
/******************************************************************************/
int PermJohnsonTrotter::factorial(int num)
{
	if (num == 1)
		return 1;
	else
		return num * factorial (num - 1);
}

/******************************************************************************/
/*!
	\brief
		Gets the current vector in the vector of vectors that contain all of the
		permutations
	\return
		Returns the current permutation
*/
/******************************************************************************/
std::vector<int> const& PermJohnsonTrotter::Get() const
{
	return permutations[count];
}

/******************************************************************************/
/*!
	\brief
		Returns false if we are at the end of the vector of permutations
	\return
		Returns true if we are not at the end of the vector, returns false if
		we are at the end of the vector of permutations
*/
/******************************************************************************/
bool PermJohnsonTrotter::Next()
{
	count++;
	if (count == numPerm)
		return false;
	else
		return true;
}

/******************************************************************************/
/*!
	\brief
		Prints the current vector within the vector of vectors of permutations
*/
/******************************************************************************/
void PermJohnsonTrotter::Print()
{
	std::vector<int> temp;
	temp.reserve(Size);          // Print the current permutation vector
	temp = permutations[count];

	for (int i = 0; i < Size; i++)
		std::cout << temp[i] << " ";

	std::cout << std::endl;
}

