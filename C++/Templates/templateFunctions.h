//---------------------------------------------------------------------------
#ifndef TEMPLATEFUNCTIONS_H
#define TEMPLATEFUNCTIONS_H
//---------------------------------------------------------------------------

namespace CS225 {

	template <typename T>
	void swap(T * left, T * right);

	template <typename T>
	void display(T const * begin, T const * end);

	template <typename T>
	T* min_element(T * begin, T * end);
	template <typename T>
	T const* min_element(T const * begin, T const * end);
	template <typename T>
	void swap_ranges(T * array, T * arrayEnd, T * array2);

	template<typename T>
	T* remove(T * array, T * arrayEnd, T item);

	template <typename T>
	void fill(T * array, T * arrayEnd, T item);
  
	template <typename T>
	int count(T * array, T * arrayEnd, T item);

	template <typename T>
	T sum(T * array, T * arrayEnd);

	template <typename T1, typename T2>
	T2* copy(T1 * array, T1 * arrayEnd, T2 * array2);

	template <typename T1, typename T2>
	bool equal(T1 * array, T1 * arrayEnd, T2 * array2);

	template <typename T>
	void replace(T * array, T * arrayEnd, T oldItem, T newItem);
  
	template <typename T>
	T* max_element(T * array, T * arrayEnd);

	template <typename T1, typename T2>
	T1* find(T1 * array, T1 * arrayEnd, const T2 item);
}
#include "templateFunctions.cpp"
#endif
