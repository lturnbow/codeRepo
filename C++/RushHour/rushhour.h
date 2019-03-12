/******************************************************************************/
/*!
\file   rushhour.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#ifndef RUSHHOUR_H
#define RUSHHOUR_H
#include <vector>
#include <tuple>
#include <cstdio>  
#include <iostream>
#include <fstream>
#include <regex>     
#include <set>
#include <map>

enum Direction   { up, left, down, right, undefined };
enum Orientation { horisontal, vertical};
std::ostream& operator<<( std::ostream& os, Direction const& d );
std::vector<std::tuple<unsigned, Direction, unsigned> > SolveRushHour( std::string const& filename );
std::vector<std::tuple<unsigned, Direction, unsigned> > SolveRushHourOptimally( std::string const& filename );

class Coordinates {
public:
	unsigned x;
	unsigned y;
};

class CarClass {
public:
	Orientation orientation;
	std::vector<Coordinates> positions;
};

class ParkingLotSolver {
    private:
		std::string filename = std::string();       // filename for data
        unsigned height             = 0;            // size of parking lot
        unsigned width              = 0;            // size of parking lot
        unsigned ** parking_lot     = nullptr;      // parking lot 
        Direction exit_direction    = undefined;    // exit direction
        unsigned car                = 0;            // car to be navigated
		std::map<unsigned, CarClass> cars;

    public:
		ParkingLotSolver(std::string const&  filename);
		~ParkingLotSolver();
		bool Solve(std::vector<std::tuple< unsigned, Direction, unsigned> > & solution, std::set<std::vector<unsigned> > & history, unsigned depth, unsigned const & max_depth);
        unsigned const& Car() const { return car; }
        Direction const& Dir() const { return exit_direction; }
		std::vector< std::tuple<unsigned, Direction, unsigned> > PossibleMoves();
		void makeMove(std::tuple< unsigned, Direction, unsigned > move);
		bool IsSolved() const;
		friend std::ostream& operator<<(std::ostream& os, ParkingLotSolver const& pl);
		void Print(std::string const& filename_out);
};
#endif
