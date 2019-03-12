/******************************************************************************/
/*!
\file   templateFunctions.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include <iostream>
#include "templateFunctions.h"

namespace CS225 {
    template <typename T>
    void display(T const *begin, T const *end)
    {
        if(begin != end) std::cout << *begin++;
        while(begin < end) {
            std::cout << ", " << *begin;
            ++begin;
        }
        std::cout << std::endl;
    }

    template <typename T>
    void swap(T *left, T *right)
    {
        T temp(*right);
        (*right) = (*left);
        (*left) = temp;
    }

    template <typename T>
    T* min_element(T *begin, T *end)
    {
        T* min = begin;
        while(begin != end) {
            if(*begin < *min) min=begin;
            ++begin;
        }
        return min;
    }

    template <typename T>
    T const* min_element(T const *begin, T const *end)
    {
        T const* min = begin;
        while(begin != end) {
            if(*begin < *min) min = begin;
            ++begin;
        }
        return min;
    }
    
	/////////////////////////////////////////////////////////////////// 
	// swap 2 ranges
	template <typename T>
	void swap_ranges(T * array, T * arrayEnd, T * array2)
	{
		for (int i = 0; (array + i) != (arrayEnd); i++)
		{
			T temp = array[i];
			array[i] = array2[i];
			array2[i] = temp;
		}
	}

	/////////////////////////////////////////////////////////////////// 
	// remove specified value from the range
	template<typename T>
	T* remove(T * array, T * arrayEnd, T item)
	{
		int counter = 0;
    int i = 0;
    
		while((array + i) != (arrayEnd))
		{
			if (array[i] == item)
			{
				counter++;
        int j = i;
        while ((array + j) < (arrayEnd - 1))
        {
					array[j] = array[j + 1];
          j++;
        }
        *arrayEnd = item;
			}
      i++;
		}
    
		return arrayEnd - counter;
	}
	/////////////////////////////////////////////////////////////////// 
	// overwrite all elements in the range with a given value
	template <typename T>
	void fill(T * array, T * arrayEnd, T item)
	{
		for (int i = 0; (array + i) != (arrayEnd); i++)
		{
			array[i] = item;
		}
	}
	/////////////////////////////////////////////////////////////////// 
	// count elements that are equal to a given value 
	template <typename T>
	int count(T * array, T * arrayEnd, T item)
	{
		int counter = 0;
		for (int i = 0; (array + i) != (arrayEnd); i++)
		{
			if (array[i] == item)
				counter++;
		}

		return counter;

	}
	/////////////////////////////////////////////////////////////////// 
	// add all element of the array together
	template <typename T>
	T sum(T * array, T * arrayEnd)
	{
		T total = 0;
		for (int i = 0;( array + i) != (arrayEnd); i++)
		{
			total += array[i];
		}

		return total;
	}
	/////////////////////////////////////////////////////////////////// 
	// copy all elements from first range into second
	template <typename T1, typename T2>
	T2* copy(T1 * array, T1 * arrayEnd, T2 * array2)
	{
		while (array != arrayEnd)
    {
      *array2 = *array;
      array++;
      array2++;
    }
		return array2;
	}
	/////////////////////////////////////////////////////////////////// 
	// compare 2 ranges, similar to copy you compare each element of the first range to a 
	template <typename T1, typename T2>
	bool equal(T1 * array, T1 * arrayEnd, T2 * array2)
	{
		while (array != arrayEnd)
    {
      if (*array2 != *array)
        return false;
      array++;
      array2++;
    }
    
    return true;
	}
	/////////////////////////////////////////////////////////////////// 
	// replace all elements in the range that are equal to old_value with a given value
	template <typename T>
	void replace(T * array, T * arrayEnd, T oldItem, T newItem)
	{
		for (int i = 0; (array + i) != (arrayEnd); i++)
		{
			if (array[i] == oldItem)
				array[i] = newItem;
		}
	}
	/////////////////////////////////////////////////////////////////// 
	// pointer to the largest element.
	template <typename T>
	T* max_element(T * array, T * arrayEnd)
	{
		T * largestPointer = array;
		for (int i = 0; (array + i) != (arrayEnd); i++)
		{
			if (array[i] > *largestPointer)
				largestPointer = (array + i);
		}

		return largestPointer;
	}
	/////////////////////////////////////////////////////////////////// 
	// pointer to the *first* element in the range that is equal to a given value
	template <typename T1, typename T2>
	T1* find(T1 * array, T1 * arrayEnd, const T2 item)
	{
		for (int i = 0; (array + i) != (arrayEnd); i++)
		{
			if (array[i] == item)
			{
				return &array[i];
			}
		}
    return arrayEnd;
	}

}
    

