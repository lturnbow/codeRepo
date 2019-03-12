/******************************************************************************/
/*!
\file   Ocean.h
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS170
\par    Assignment #2
\date   2/11/2016
\brief  
    This file includes the Ocean class member functions, private members, and
	public members.
	
*/
/******************************************************************************/
////////////////////////////////////////////////////////////////////////////////
#ifndef OCEAN_H
#define OCEAN_H
////////////////////////////////////////////////////////////////////////////////

#include "WarBoats.h"

namespace CS170
{
  namespace WarBoats
  {
    const int BOAT_LENGTH = 4;  // Length of a boat
    const int HIT_OFFSET = 100; // Add this to the boat ID

    class Ocean
    {
      public:
		// Constructor
		Ocean(int num_boats, int x_quadrants, int y_quadrants);
		// Destructor
		~Ocean();
		ShotResult TakeShot(const Point &coordinate);
		BoatPlacement PlaceBoat(const Boat &boat);
		ShotStats GetShotStats() const;
        const int *GetGrid() const;
        Point GetDimensions() const;

      private:
        int *grid_;        // The 2D ocean
        int x_quadrants_;  // Ocean size along x-axis
        int y_quadrants_;  // Ocean size along y-axis
		
		int num_boats_;    // Number of boats
		Boat *boats;       // Boat array
		ShotStats stats;   // Stats for game
    }; // class Ocean

  } // namespace WarBoats

} // namespace CS170

#endif // OCEAN_H
////////////////////////////////////////////////////////////////////////////////
