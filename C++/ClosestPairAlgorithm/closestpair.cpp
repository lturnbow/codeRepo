/******************************************************************************/
/*!
\file   closestpair.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include "closestpair.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <utility>
#include <vector>

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
std::ostream& operator<< (std::ostream& os, Point const& p) {
	os << "(" << p.x << " , " << p.y << ") ";
	return os;
}

/******************************************************************************/
/*!
	\brief
		Stream operator
	\param os
		Input stream object
	\param p
		Point to take in
	\return
		Returns input stream
*/
/******************************************************************************/
std::istream& operator>> (std::istream& os, Point & p) {
	os >> p.x >> p.y;
	return os;
}

/******************************************************************************/
/*!
	\brief
		Function that compares points for standard sort by X coordinate
	\param lhs
		First point
	\param rhs
		Second point
	\return
		Returns a bool if they need to be swapped
*/
/******************************************************************************/
bool cmpX(Point lhs, Point rhs)
{
	return lhs.x < rhs.x;
}

/******************************************************************************/
/*!
	\brief
		Function that compares points for standard sort by Y coordinate
	\param lhs
		First point
	\param rhs
		Second point
	\return
		Returns a bool if they need to be swapped
*/
/******************************************************************************/
bool cmpY(Point lhs, Point rhs)
{
	return lhs.y < rhs.y;
}

/******************************************************************************/
/*!
	\brief
		Finds the distance between two points
	\param one
		First point
	\param two
		Second point
	\return
		Returns the distance as a float
*/
/******************************************************************************/
float dist(Point one, Point two)
{
	return sqrt((one.x - two.x) * (one.x - two.x) + 
				(one.y - two.y) * (one.y - two.y));
}

/******************************************************************************/
/*!
	\brief
		Finds the distance between all of the points in the epsilon vector that
		contain the points that could possibly have a smaller distance apart
		than the current minimum, but have not yet been calculated because
		they are on different sides of the plot
	\param epsilon
		The vector of points that contain the points on the strip
	\param minimum
		The current minimum
	\return
		Returns a float of the new (or old) minimum value
*/
/******************************************************************************/
float stripClosest(std::vector<Point> epsilon, float minimum)
{
	float min = minimum; // Current minimum passed into the function
	unsigned int epSize = epsilon.size();
	unsigned int i = 0;
	unsigned int j;
	while (i < epSize)
	{
		j = i + 1;
		while (j < epSize && (epsilon[j].y - epsilon[i].y) < min)
		{
			float distance = dist(epsilon[i], epsilon[j]);
			if (distance < min)   // Replace min if new distance is smaller
				min = distance;
			j++;
		}
		i++;
	}
	return min;
}

/******************************************************************************/
/*!
	\brief
		Recursive function that continuously looks for the smallest distance
		between two points of a plot until the base case is reached
	\param xVector
		A vector of all the points sorted by x coordinate
	\param yVector
		A vector of all the points sorted by y coordinate
	\param size
		The size of the vectors
	\return
		Returns the minimum found
*/
/******************************************************************************/
float closestPair_aux (std::vector<Point> xVector, std::vector<Point> yVector, 
					   unsigned int size, bool sameX) 
{
	if (size == 2)    // Base case for having only two points
		return dist(xVector[0], xVector[1]);
	if (size == 3)    // Base cast for three points, return minimum distance
	{
		float dist1 = dist(xVector[0], xVector[1]);
		float dist2 = dist(xVector[1], xVector[2]);
		return dist1 < dist2 ? dist1 : dist2;
	}

	unsigned int median = size / 2;  // Median, middle of list
	std::vector<Point> leftVector;   // Right and left vector for splitting up
	std::vector<Point> rightVector;  // the plot

	leftVector.reserve(size);
	rightVector.reserve(size);

	// If the x values are not the same, do x-ordering
	if (sameX == false)
	{
		unsigned int i = 0; 
		// Pushing the first half of the x vector onto the left vector, since 
		// the x vector is sorted by x coordinate, and stopping when the value
		// at the median is reached
		//unsigned int newSize = 0;
		while (xVector[i].x <= xVector[median].x && i < size) {
			leftVector[i] = xVector[i];
			i++;
		}

		unsigned int j = 0;
		// Pushing values greater than the median value onto the right vector
		while (i < size && j < size) // Pushing the rest onto the right vector
		{		
			rightVector[j] = xVector[i];
			i++; 
			j++; 
		}
	}	
	
	// If the x values are all the same, do y-ordering, looking at the y 
	// coordinates instead of the x coordinates
	else if (sameX == true)
	{
		unsigned int i = 0; 
		// Pushing the first half of the x vector onto the left vector, since 
		// the x vector is sorted by x coordinate, and stopping when the value
		// at the median is reached
		while (xVector[i].y <= xVector[median].y && i < size) {
			leftVector[i] = xVector[i];
			i++;
		}

		unsigned int j = 0;
		// Pushing values greater than the median value onto the right vector
		while (i < size && j < size) // Pushing the rest onto the right vector
		{		
			rightVector[j] = xVector[i];
			i++; 
			j++; 
		}
	}
	
	// Calculating the left minimum recusrively given the left vector
	float leftMin = closestPair_aux(xVector, leftVector, median, sameX);

	// Putting second half of xvector into a new array so it doesn't have a
	// variable size
	std::vector<Point> temp;
	temp.resize(size);
	unsigned int j = 0;
	unsigned int newSize = 0;
	for (unsigned int i = median; i < size && j < size; i++, j++) {

		temp[j] = xVector[i];
		newSize++;
	}
	temp.resize(newSize);
	
	// Calculating the right minimum recursively given the right vector
	float rightMin = closestPair_aux(temp, rightVector, size - median, sameX);
	
	// Finding the minimum between the two float minimums that were found
	// recursively
	float minimum = leftMin < rightMin ? leftMin : rightMin;
	
	// A vector to hold the strip points that could possibly have a smaller 
	// distance between them than the current minimum
	std::vector<Point> epsilon; 
	epsilon.resize(size);
	newSize = 0;
	// Finding all of the points that could have a smaller minimum distance and
	// adding them to the strip vector
	unsigned int i = 0; 
	unsigned int ySize = yVector.size();;
	while (i < ySize)
	{
		if (yVector[i].x - xVector[median].x > minimum || 
			xVector[median].x - yVector[i].x < minimum)  {
			epsilon[newSize] = yVector[i];
			newSize++;
		}
		i++;
	}
	epsilon.resize(newSize);
	
	// Calculating the minimum of the strip
	float stripMin = stripClosest(epsilon, minimum);
	// Finding the minimum between the strip and the current minimum
	float returnMin = minimum < stripMin ? minimum : stripMin;
	return returnMin;
}

/******************************************************************************/
/*!
	\brief
		The intial function called to start the recusrive function to find the
		minimum distance between two points
	\param points
		The vector that contains all the points on the plot
	\return
		Returns a float of the minimum distance between two points as calculated
		by the recursive function
*/
/******************************************************************************/
float closestPair (std::vector<Point> const& points) 
{
	unsigned int size = points.size();
	
	if (size==0) throw "zero size subset";
	if (size==1) return std::numeric_limits<float>::max();
	
	// Copying all points from point vector into x and y vectors
	std::vector<Point> xVector;
	std::vector<Point> yVector;
	xVector.reserve(size);
	yVector.reserve(size);
	xVector = points;
	yVector = points;
	
	// Sorting the xvector and yvector by x and y, respectively
	std::sort(xVector.begin(), xVector.end(), cmpX);
	std::sort(yVector.begin(), yVector.end(), cmpY);
	
	// Searching to see if all of the points are the same. If they are, return 0
	// If all of the x values are the same, switch to y-ordering
	bool sameX = true;
	bool sameY = true;
	for (unsigned int i = 0; i < size - 1; i++)
	{
		// Break if different x values are found, points are not all the same
		// and x values are different
		if (xVector[i].x != xVector[i + 1].x) 
		{
			sameX = false;
			break;
		}
		// If different y values are found, set y value to false, but continue
		// checking the x values
		if (yVector[i].y != yVector[i + 1].y)
		{
			sameY = false;
			if (sameX == false)
				break;
		}
	}
	
	// If all the points are the same, just return 0 without going through any
	// calculations
	if (sameX == true && sameY == true)
		return 0.0f;
	
	return closestPair_aux(xVector, yVector, size, sameX);
}

