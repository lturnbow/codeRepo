/******************************************************************************/
/*!
\file   knapsack-dp.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include "knapsack-dp.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <algorithm>

Item::Item(int const& weight, int const& value)
	: weight(weight), value(value)
{

}

Item::Item(Item const& original)
	: weight(original.weight), value(original.value)
{
}

/******************************************************************************/
/*!
	\brief
		Stream operator
	\param os
		Output stream object
	\param p
		Point to output
	\return
		Returns output stream
*/
/******************************************************************************/
std::ostream& operator<< (std::ostream& os, Item const& item) {
	os << "(" << item.weight << " , " << item.value << ") ";
	return os;
}

/******************************************************************************/
/*!
	\brief
		Stream operator
	\param os
		Input stream object
	\param p
		Point to input
	\return
		Returns input stream
*/
/******************************************************************************/
std::istream& operator >> (std::istream& os, Item & item) {
	os >> item.weight >> item.value;
	return os;
}

typedef std::vector< std::vector<int> > Table; //2-dimensional table

/******************************************************************************/
/*!
	\brief
		Returns maximum element
	\param a
		First parameter to compare
	\param b
		Second parameter to compare
	\return
		Returns max of two elements
*/
/******************************************************************************/
int max(int a, int b)
{
	return a > b ? a : b;
}

/******************************************************************************/
/*!
	\brief
		Solves the knapsack problem using dynamic programming
	\param items
		Vector of items
	\param W
		Total weight that the knapsack can hold
	\return
		Returns a vector of the indices of the items that are included in the
		solution
*/
/******************************************************************************/
std::vector<int> knapsackDP(std::vector<Item> const& items, int const& W) {
	int num_items = items.size();
	
	// Declare 2-D vector with dimensions of number of items by total weight
	std::vector<std::vector<int> > Table(num_items + 1, std::vector<int>(W + 1, 0));
	std::vector<int> bag;

	// Going through table, calculate the items that can be put into the knapsack
	// by using the dynamic programming approach
	for (int i = 1; i <= num_items; i++)
	{
		for (int j = 0; j <= W; j++)
		{
			if (items[i - 1].weight > j)
				Table[i][j] = Table[i - 1][j];
			else
				Table[i][j] = max(Table[i - 1][j], Table[i - 1][j - items[i - 1].weight] + items[i - 1].value);
		}
	}

	if (num_items + W < 50) {
		std::cout << "   ";
		for (int n = 0; n <= num_items; ++n) { std::cout << n << "     "; }
		std::cout << "  items\n        ";
		for (int n = 0; n<num_items; ++n) { std::cout << items[n].weight << "," << items[n].value << "   "; }
		std::cout << "\n   ";
		for (int n = 0; n <= num_items; ++n) { std::cout << "------"; }
		std::cout << std::endl;

		for (int w = 0; w <= W; ++w) {
			std::cout << w << "| ";
			for (int n = 0; n <= num_items; ++n) {
				std::cout << Table[n][w] << "     ";
			}
			std::cout << std::endl;
		}
	}
	
	// The optimum value is the value at the bottom right of the table
	int largest = Table[num_items][W];
	int j = W;
	int i = num_items;
	// Going through table to detect which items were included in the answer
	while (i > 0)
	{
		// Looking for two items next to each other that add up to the number
		// that we want and are the required weight
		if (i > 2 && items[i - 1].weight + items[i - 2].weight == W && items[i - 1].value + items[i - 2].value == largest)
		{
			bag.clear();
			bag.push_back(i - 1);
			bag.push_back(i - 2);
			return bag;
		}
		// Otherwise, look through the table by retracing steps of what we did
		// to find the value previously
		if (Table[i][j] == Table[i - 1][j - items[i - 1].weight] + items[i - 1].value)
		{
			bag.push_back(i - 1);
			i--;
			j -= items[i].weight;
		}
		else
			i--;
	}

	return bag;
}

int valueBag( std::vector<Item> const& items, std::vector<int> const& bag ) {
	std::vector<int>::const_iterator it   = bag.begin(),
	it_e = bag.end();
	int accum = 0;
	for ( ; it != it_e; ++it) { accum += items[ *it ].value; }
	return accum;
}

/******************************************************************************/
/*!
	\brief
		Recursive function to find the items in the knapsack
	\param items
		Vector of all items
	\param W
		Total weight that knapsack can hold
	\param index
		Index of current location going through table and item vector
	\param table
		Table to hold calculated values
	\return
		Returns solution to knapsack problem
*/
/******************************************************************************/
int knapsackRecMemAux(std::vector<Item> const& items, int const& W, int index, Table & table) 
{
	int value;
	// Going through table and calculating if the table value is -1
	if (table[index][W] < 0) 
	{
		// Setting the value to the previous table value if the weight is
		// greater than the desired weight
		if (items[index - 1].weight > W)
			value = knapsackRecMemAux(items, W, index - 1, table);

		// Otherwise find the max value 
		else
			value = max(knapsackRecMemAux(items, W, index - 1, table), items[index - 1].value 
				+ knapsackRecMemAux(items, W - items[index - 1].weight, index - 1, table));

		// Set the table value at the particular indices to the newly calculated
		// value
		table[index][W] = value;
	}
	
	return table[index][W];
}

/******************************************************************************/
/*!
	\brief
		Function that initially calls the knapsack recursive function
	\param items
		Vector of items
	\param W
		Total weight that knapsack can hold
	\return
		Returns a items that are in the solution to the knapsack problem
*/
/******************************************************************************/
std::vector<int> knapsackRecMem( std::vector<Item> const& items, int const& W ) 
{
	int num_items = items.size();
	// Initialize table to specified size and set all values of the table to -1
	std::vector<std::vector<int> > Table(num_items + 1, std::vector<int>(W + 1, -1));

	// Change all values in the 0th row and colulmn to 0
	for (int i = 0; i <= num_items; i++)
		Table[i][0] = 0;

	for (int i = 0; i <= W; i++)
		Table[0][i] = 0;
	

	// Call the recursive function to find the largest value of the knapsack
	// solution
	int largest = knapsackRecMemAux(items, W, num_items, Table);

	if ( num_items + W < 50 ) { //print only if table is not too big
	std::cout << "   ";
	for ( int n=0; n<=num_items; ++n) { std::cout << n << "     "; }
	std::cout << "  items\n        ";
	for ( int n=0; n<num_items; ++n) {
	std::cout << items[n].weight << "," << items[n].value<<"   ";
	}
	std::cout << "\n   ";
	for ( int n=0; n<=num_items; ++n) { std::cout << "------"; }
	std::cout << std::endl;

	for ( int w=0; w<=W; ++w) {
	std::cout << w << "| ";
	for ( int n=0; n<=num_items; ++n) {
	std::cout << Table[n][w] << "     ";
	}
	std::cout << std::endl;
	}
	}

	// Finding the items that were in the solution 
	std::vector<int> bag;
	int j = W;
	int i = num_items;
	while (i > 0)
	{
		if (i > 2 && items[i - 1].weight + items[i - 2].weight == W && items[i - 1].value + items[i - 2].value == largest)
		{
			bag.clear();
			bag.push_back(i - 1);
			bag.push_back(i - 2);
			return bag;
		}
		if (Table[i][j] == Table[i - 1][j - items[i - 1].weight] + items[i - 1].value)
		{
			bag.push_back(i - 1);
			i--;
			j -= items[i].weight;
		}
		else
			i--;
	}

	return bag;
}
