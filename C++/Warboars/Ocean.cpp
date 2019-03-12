/******************************************************************************/
/*!
\file   Ocean.cpp
\author Lauren Turnbow
\brief  
    This file implements the game Battleship by creating a class called ocean
    that is used to build an ocean, place boats in it, and take shots. 
    The player will attempt to sink each boat and each attempt will be 
    determined to be a hit, sink, miss, duplicate, or illegal move.
      
    Functions include:
        - Ocean
        - ~Ocean
        - TakeShot
        - PlaceBoat
        - GetShotStats
        - GetGrid
        - GetDimensions
*/
/******************************************************************************/
#include "WarBoats.h"
#include "Ocean.h"

namespace CS170
{
  namespace WarBoats
  {
/******************************************************************************/
/*!
  \class Ocean
  
  \brief  
    The Ocean class creates an ocean object and allocates memory for a boat
    array and the array for the grid that will be used as the game board.

  \param num_boats
    Number of boats that will be placed in the ocean.

  \param x_quadrants
    The size of the x-axis of the grid.
    
  \param y_quadrants
    The size of the y-axis of the grid.

*/
/******************************************************************************/
    Ocean::Ocean(int num_boats, int x_quadrants, int y_quadrants)
    {
      // Allocating memory for boat and grid arrays
      boats = new Boat [num_boats];
      grid_ = new int [x_quadrants * y_quadrants];
      
      // Declaring private variables with variables passed to function
      num_boats_ = num_boats;
      x_quadrants_ = x_quadrants;
      y_quadrants_ = y_quadrants;
      
      // Initializing stats 
      stats.hits = 0;
      stats.misses = 0;
      stats.duplicates = 0;
      stats.sunk = 0;
      
      // Initalizing grid values to zero
     for (int i = 0; i < x_quadrants_ * y_quadrants_; i++)
        grid_[i] = 0;
     
     // Initializing boat array to zero
      for (int i = 0; i < num_boats_; i++)
        boats[i].hits = 0;
    }
/******************************************************************************/
/*!
  \class Ocean
  
  \brief
    The destructor for an ocean object. Deletes memory that was allocated for
    the boat array and the grid.
  
*/
/******************************************************************************/
    Ocean::~Ocean()
    {
      // Free memory that was used for the grid and the boats
      delete [] grid_;
      delete [] boats;
    }
    
/******************************************************************************/
/*!
  \class Ocean
  
  \brief
    Determines if a shot taken (a coordinate point) hit a boat, missed, 
    sunk, was a duplicate, or was an illegal move.

  \param coordinate
    The shot that is to be taken, given by a coordinate point.
        
  \return
    Returns the result of if the boat was hit, missed, sunk, duplicate
    hit, or illegal.

*/
/******************************************************************************/
    ShotResult Ocean::TakeShot(const Point &coordinate)
    {
      // The boat ID that was just hit, save to add HIT_OFFSET to
      int boatID = grid_[coordinate.y * x_quadrants_ + coordinate.x];
      
      // ILLEGAL
      // If the coordinates given are outside of the board
      if (coordinate.x < 0 || coordinate.x > x_quadrants_ || 
        coordinate.y < 0 || coordinate.y > y_quadrants_)
        return srILLEGAL;
      
      // MISS
      // If there is no boat at coordinate (a zero), it is a miss
      if (grid_[coordinate.y * x_quadrants_ + coordinate.x] == dtOK)
      {
        stats.misses++;
        // Assign that position to -1 to show it was a miss
        grid_[coordinate.y * x_quadrants_ + coordinate.x] = dtBLOWNUP;
        return srMISS;
      }
        
      // DUPLICATE
      // If coordinate had already been hit and was a miss or is a boat that 
      //   was already hit
      if (grid_[coordinate.y * x_quadrants_ + coordinate.x] == 
        dtBLOWNUP || grid_[coordinate.y * x_quadrants_ + 
        coordinate.x] > HIT_OFFSET)
      {
        stats.duplicates++;
          return srDUPLICATE;
      }
      
      // HIT 
      // If the coordinate holds a BOAT_ID to show there is part of a boat there
      if (grid_[coordinate.y * x_quadrants_ + coordinate.x] > dtOK && 
       grid_[coordinate.y * x_quadrants_ + coordinate.x] < HIT_OFFSET)
      {
        // Increment BOAT_ID with HIT_OFFSET to show the boat has been hit
        grid_[coordinate.y * x_quadrants_ + coordinate.x] += HIT_OFFSET;
        stats.hits++;
        // Incrememnt number of hits in the boat array
        boats[boatID - 1].hits++;
        // SUNK
        // If all positions of the boat have been hit
        if (boats[boatID - 1].hits == BOAT_LENGTH)
        {
          stats.sunk++;
          return srSUNK;
        }
          return srHIT;
      }
        
      else
        return srILLEGAL;
    }

/******************************************************************************/
/*!
  \Class Ocean
  
  \brief
    Places a boat in the ocean.

  \param boat
    A reference to the boat that will be placed in the ocean.
        
  \return
    Returns if the boat was placed successfully in the ocean or not.
*/
/******************************************************************************/
    BoatPlacement Ocean::PlaceBoat(const Boat &boat)
    {
      // If boat can be successfully placed in grid
      BoatPlacement result = bpREJECTED;  
      
      // New variables declared so they can be modified
      int xBoat = boat.position.x;    // x position of the boat
      int yBoat = boat.position.y;    // y position of the boat
      
      // VERTICAL BOATS
      if (boat.orientation == oVERTICAL)
      {
        // Add boat length to boat. If left y-coordinate is outside of grid, 
        //  the while boat is
        yBoat += BOAT_LENGTH;  
        
        if (yBoat > y_quadrants_)
          result = bpREJECTED;
      
        // If boat has a negative y - coordinate
        else if (yBoat < 0)
          result = bpREJECTED;
      
        // If boat has a negative x-coordinate or is outside of x_quadrant limit
        else if (boat.position.x < 0 || boat.position.x > x_quadrants_)
            result = bpREJECTED;
      
        // If boat is inside of the grid
        else
        {
          result = bpACCEPTED;
          for (int i = 0; i < BOAT_LENGTH; i++)
          {
            // If there is not already a boat there
            if (grid_[(boat.position.y + i) * x_quadrants_ + 
                boat.position.x] == 0)
              result = bpACCEPTED;
            else
            {
              // Can't place boat if there is already a boat there
              result = bpREJECTED;
              break;
            }
          }
        }
            
        if (result == bpACCEPTED)
        {
          // Place boat inside of grid by changing the elements to the BOAT_ID
          for (int i = 0; i < BOAT_LENGTH; i++)
            grid_[(boat.position.y + i) * x_quadrants_ + 
                boat.position.x] = boat.ID;
        }
                   
        return result;
      }
      
      // HORIZONTAL BOATS
      if (boat.orientation == oHORIZONTAL)
      {
        // Add boat length to boat. If top x-coordinate is outside of grid, 
        //  the while boat is
        xBoat += BOAT_LENGTH;
        
        if (xBoat > x_quadrants_)
          result = bpREJECTED;
      
        // If boat has a negative x-coordinate
        else if (xBoat < 0)
          result = bpREJECTED;
      
        // If boat has a negative y-coordinate or is outside of y_quadrant limit
        else if (boat.position.y < 0 || boat.position.y > y_quadrants_)
            result = bpREJECTED;
        
        // If boat is inside of the grid
        else 
        {
          for (int i = 0; i < BOAT_LENGTH; i++)
          {
            // If there is not already a boat there
            if (grid_[boat.position.y * x_quadrants_ + boat.position.x
                + i] == 0)
              result = bpACCEPTED;
            // Can't place boat if there is already a boat there
            else
            {
              result = bpREJECTED;
              break;
            }
          }
        }
            
        if (result == bpACCEPTED)
        {
          // Place boat inside of grid by changing the elements to the BOAT_ID
          for (int i = 0; i < BOAT_LENGTH; i++)
            grid_[boat.position.y * x_quadrants_ + boat.position.x + 
                i] = boat.ID;
        }
        
        return result;
      }
            
        else 
          return result;
    }

/******************************************************************************/
/*!
  \Class Ocean
  
  \brief
    Returns the grid of the ocean.
       
  \return
    Returns a pointer to the grid array of constant ints.
*/
/******************************************************************************/
    const int *Ocean::GetGrid() const
    {
      return grid_;
    }

/******************************************************************************/
/*!
  \class Ocean
  
  \brief  
    Returns the dimensions of a point

  \return
    Returns a point with x and y coordinates.

*/
/******************************************************************************/
    Point Ocean::GetDimensions() const
    {
      Point pt = {x_quadrants_, y_quadrants_};
      return pt;
    }

/******************************************************************************/
/*!
  \class Ocean
  
  \brief  
    Returns the shot stats of the game

  \return 
    Returns the shot stats of the game

*/
/******************************************************************************/
    ShotStats Ocean::GetShotStats() const
    {
      return stats;
    }

  } // namespace WarBoats

} // namespace CS170

