/******************************************************************************/
/*!
\file   hull-bruteforce.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include "hull-bruteforce.h"
#include <algorithm>
#include <iostream>

/******************************************************************************/
/*!
	\brief
		comparison operator for point
	\param arg2 
		Second argument
	\return
		Returns if they are equal
*/
/******************************************************************************/
bool Point::operator==(Point const& arg2) const {
	return ((x == arg2.x) && (y == arg2.y));
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
std::istream& operator >> (std::istream& os, Point & p) {
	os >> p.x >> p.y;
	return os;
}

/******************************************************************************/
/*!
	\brief
		Gets the location of the given point, using the given line (two points)
	\param p1x
		x coordinate of first point
	\param p1y
		y coordinate of first point
	\param p2x	
		x coordinate of second point
	\param p2y
		y coordinate of second point
	\param qx
		x coordinate of point we are finding the location of
	\param qy 
		y coordinate of point we are finding the location of
	\return
		Returns a pair of bools for the left or right side
*/
/******************************************************************************/
//return value is (on left, on right)
std::pair<bool, bool> get_location(
	float const& p1x, //check which side of the line (p1x,p1y)-->(p2x,p2y) 
	float const& p1y, //point (qx,qy) is on
	float const& p2x, float const& p2y, float const& qx, float const& qy)
{
	Point dir = { p2x - p1x,p2y - p1y };
	Point norm = { dir.y, -dir.x };
	Point point = { qx - p1x,qy - p1y };
	//scalar product is positive if on right side
	float scal_prod = norm.x*point.x + norm.y*point.y;
	return std::make_pair((scal_prod<0), (scal_prod>0));
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////Helper Functions////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/******************************************************************************/
/*!
	\brief
		Finds the cross product of two, 2-D points
	\param one		
		First point
	\param two
		Second point
	\return
		Returns the cross product
*/
/******************************************************************************/
float CrossProduct(Point one, Point two)
{
	return (one.x * two.y) - (two.x * one.y);
}

/******************************************************************************/
/*!
	\brief
		Calculates the turn of three given points
	\param p
		Vector that contains the points to be used
	\return
		Returns the cross product
*/
/******************************************************************************/
float calculateCrossProduct(std::vector<Point> p)
{
	Point Lupperp0, Lupperp1, Lupperp2, p0, p1;
	Lupperp0 = p[p.size() - 3];
	Lupperp1 = p[p.size() - 2];
	Lupperp2 = p[p.size() - 1];
	p0.x = Lupperp2.x - Lupperp1.x;
	p0.y = Lupperp2.y - Lupperp1.y;
	p1.x = Lupperp1.x - Lupperp0.x;
	p1.y = Lupperp1.y - Lupperp0.y;
	return CrossProduct(p0, p1);
}

/******************************************************************************/
/*!
	\brief
		Function that compares points for standard sort
	\param lhs
		First point
	\param rhs
		Second point
	\return
		Returns a bool if they need to be swapped
*/
/******************************************************************************/
bool cmp(Point lhs, Point rhs)
{
	return lhs.x < rhs.x;
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/******************************************************************************/
/*!
	\brief
		Returns a set of indices that correspond to the convex hull
	\param points	
		A vector that contains the points
	\return
		Returns a set of indices corresponding to the points of the hull
*/
/******************************************************************************/
std::set<int> hullBruteForce(std::vector<Point> const& points) {
	int num_points = points.size();
	if (num_points < 3) throw "bad number of points";
	
	std::set<int> hull_indices;
	std::pair<bool, bool> location = std::make_pair(0, 0);
	std::pair<bool, bool> startingPair = std::make_pair(0, 0);
	std::pair<bool, bool> prevLocation;
	int onOneSide = 0;
	int index1 = 0;
	int index2 = 1;
	int startingPoint = 1;

	// For each pair determine whether all other points are on one side of the 
	// line formed by the pair of points. If it does - add the index of the 
	// point to the hull
	
	// Going through all of the points
	for (std::vector<Point>::const_iterator it = points.begin(); 
									   it != points.end(); ++it)
	{
		Point p = *it;
	    float x = p.x;
		float y = p.y;
		// Going through the rest of the points
		for (std::vector<Point>::const_iterator it2 = it + 1; 
								  it2 != points.end(); ++it2)
		{
			Point p2 = *it2;
			float x2 = p2.x;
			float y2 = p2.y;
			onOneSide = 0;
			prevLocation == startingPair;
			location = startingPair;
			for (std::vector<Point>::const_iterator otherPoints = points.begin()
								   ; otherPoints != points.end(); ++otherPoints)
			{
				// Skip if they are the same point
				if (*otherPoints == *it || *otherPoints == *it2)
					continue;
				Point currentPoint = *otherPoints;
				float currentX = currentPoint.x;
				float currentY = currentPoint.y;

				prevLocation = location;

				// Get location of point
				location = get_location(x, y, x2, y2, currentX, currentY);
				
				// Continue if this is the first point
				if (prevLocation == startingPair)
					continue;
				// If the points are on the same side so far
				else if (prevLocation == location)
				{
					onOneSide = 1;
					continue;
				}
				// If the current and previous points are on different sides
				else if (prevLocation != location)
				{
					onOneSide = 0;
					break;
				}
			}

			// If all points are on one side, add the indices of the two points
			// to the hull
			if (onOneSide == 1)
			{
				hull_indices.insert(index1);
				hull_indices.insert(index2);
			}
			index2++;
			if (index2 == num_points) // reset the index if it's at the max
			{
				index2 = startingPoint + 1;
				startingPoint++;
			}
		}
		index1++;
	}

	return hull_indices;
}

/******************************************************************************/
/*!
	\brief
		Returns a set of indices that correspond to the convex hull
	\param points	
		A vector that contains the points
	\return
		Returns a vector of indices corresponding to the points of the hull
*/
/******************************************************************************/
std::vector<int> hullBruteForce2(std::vector< Point > const& points) 
{
	int num_points = points.size();
	if (num_points < 3) throw "bad number of points";

	std::vector<int> hull_indices;
	std::vector<Point> nonconstV = points;
	std::vector<Point> NC = points;
	std::vector<Point> Lupper, Lower;

	// Sort the vector by x coordinate
	std::sort(nonconstV.begin(), nonconstV.end(), cmp);
	float currentCross;
	// Add the first two points to the Lupper vector
	Lupper.push_back(nonconstV[0]);
	Lupper.push_back(nonconstV[1]);
	for (unsigned int i = 2; i < nonconstV.size(); i++)
	{
		// Push the next point onto the Lupper vector
		Lupper.push_back(nonconstV[i]);
		// Calculate the cross product of the last three points in Lupper
		currentCross = calculateCrossProduct(Lupper);
		// While there are three points and the cross product is negative
		while (Lupper.size() > 2 && currentCross < 0) {
			// Theres a left turn, erase the middle point
			Lupper.erase(Lupper.begin() + (Lupper.size() - 2));
			// Recalculate the cross product for the next iteration
			if (Lupper.size() > 2)
				currentCross = calculateCrossProduct(Lupper);
		}
	}

	// Reverse the vector for the lower portion of the hull
	std::reverse(nonconstV.begin(), nonconstV.end());
	// Push back the first two points onto the Lower vector
	Lower.push_back(nonconstV[0]);
	Lower.push_back(nonconstV[1]);

	for (unsigned int i = 2; i < nonconstV.size(); i++)
	{
		// Push back the next point onto the Lower vector
		Lower.push_back(nonconstV[i]);
		// Caclulate the cross product of the last three points in Luupper2
		currentCross = calculateCrossProduct(Lower);
		// While theres 3 points in the list and the cross product is negative
		while (Lower.size() > 2 && currentCross < 0) {
			// Erase the middle point of the 3
			Lower.erase(Lower.begin() + (Lower.size() - 2));
			if (Lower.size() > 2)
				currentCross = calculateCrossProduct(Lower);
		}
	}
	// Erase the first and last points of the lower hull
	Lower.erase(Lower.begin());
	Lower.erase(Lower.begin() + Lower.size() - 1);

	bool added = false;
	int size = NC.size();
	// Getting rid of the points that are not in the hull
	for (int i = size - 1; i >= 0; i--)
	{
		added = false;
		// Looking through Lupper vector of hull for a match
		for (unsigned int j = 0; j < Lupper.size(); j++)
			if (NC[i] == Lupper[j])
				added = true;

		// Looking through lower vector of hull for a match
		for (unsigned int k = 0; k < Lower.size(); k++)
			if (NC[i] == Lower[k])
				added = true;

		if (added == false) // If the current point was not added, delete it
			NC.erase(NC.begin() + i);
	}
	std::vector<Point> xVec = NC;
	std::vector<Point> temp;      			  // Temp to hold order of points			 
	std::sort(xVec.begin(), xVec.end(), cmp); // Sort by x coordinate
	
	Point p;
	p = xVec[xVec.size() - 1];    // Start with right most point
	// If the first and second point of the list has the same x-coordinate, take
	// the one with the lower y-value
	if (xVec[xVec.size() - 1].x == xVec[xVec.size() - 2].x)
	{
		if (xVec[xVec.size() - 1].y < xVec[xVec.size() - 2].y)
			p = xVec[xVec.size() - 1];
		else
			p = xVec[xVec.size() - 2];
	}
	temp.push_back(p);  // Push the first point onto the temp vector

	// Erase the current point from the list
	xVec.erase(std::remove(xVec.begin(), xVec.end(), p), xVec.end());
	float currX = p.x;
	float currY = p.y;

	for (int i = xVec.size() - 1; i >= 0; i--)
	{	
		// If the next point has an x-value less than the current value and a
		// y value greater than the current point, take that point
		if (xVec[i].x <= currX && xVec[i].y >= currY)
		{
			// Push the current point onto the temp vector, and erase it from 
			// the x value list
			temp.push_back(xVec[i]);
			Point p = xVec[i];
			xVec.erase(std::remove(xVec.begin(), xVec.end(), p), xVec.end());
		}
	}
	
	// Adding the lower points to the temp vector
	while (xVec.size())
	{
		temp.push_back(xVec[0]);
		Point p = xVec[0];
		xVec.erase(std::remove(xVec.begin(), xVec.end(), p), xVec.end());
	}

	// Matching the points with their original indices and adding them to the 
	// hull_indices vector
	for (unsigned int i = 0; i < temp.size(); i++)
	{
		int count = 0;
		for (unsigned int j = 0; j < points.size(); j++)
		{
			if (temp[i] == points[j])
				hull_indices.push_back(count);
			count++;
		}
	}

	return hull_indices;
}

