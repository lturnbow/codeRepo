/******************************************************************************/
/*!
\file   rushhour.cpp
\author Lauren Turnbow
*/
/******************************************************************************/
#include <iostream>
#include "rushhour.h"
#include <fstream>
#include <string>
#include <algorithm>

/******************************************************************************/
/*!
	\brief
		Function that is solves rush hour given the solve function

	\param filename
		Name of file that the data is stored in

	\return
		Returns the solution of the board
*/
/******************************************************************************/
std::vector< std::tuple<unsigned, Direction, unsigned> > SolveRushHour(std::string const& filename)
{
	ParkingLotSolver lot(filename);
	std::set<std::vector<unsigned> > history;
	std::vector<std::tuple<unsigned, Direction, unsigned> > solution;
	unsigned depth = 1, maxdepth = 30;
	lot.Solve(solution, history, depth, maxdepth);
	std::reverse(solution.begin(), solution.end());
	return solution;
}

/******************************************************************************/
/*!
	\brief
		Function that is solves rush hour optimally given the solve function

	\param filename
		Name of file that the data is stored in

	\return
		Returns the solution of the board
*/
/******************************************************************************/
std::vector< std::tuple<unsigned, Direction, unsigned> > SolveRushHourOptimally(std::string const& filename)
{
	ParkingLotSolver lot(filename);
	std::set<std::vector<unsigned> > history;
	std::vector<std::tuple<unsigned, Direction, unsigned> > solution;
	unsigned depth = 1,  maxdepth = 1;
	while (maxdepth < 1000)
	{
		if (lot.Solve(solution, history, depth, maxdepth))
			break;
		maxdepth++;
	}

	std::reverse(solution.begin(), solution.end());
	return solution;
}

/******************************************************************************/
/*!
	\brief
		Constructor for the parking lot

	\param filename
		Name of file that the data is stored in
*/
/******************************************************************************/
ParkingLotSolver::ParkingLotSolver(std::string const&  filename) : filename(filename)
{
	std::ifstream infile(filename);
	std::string   data; 

	if (!infile.is_open()) {
		std::cerr << "Errors in input file: cannot open \"" << filename << "\"" << std::endl;
		throw "Errors in input file: cannot open";
	}

	while (!infile.eof()) {
		std::string line;
		std::getline(infile, line);
		data.append(line);
		data.append(" ");
	}

	infile.close();
	std::smatch match;

	if (std::regex_match(data, match, std::regex(".*width\\s+(\\d+).*", std::regex_constants::icase)) && match.size() == 2) {
		width = std::stoi(match[1]);
		data = std::regex_replace(data, std::regex("width\\s+\\d+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"width\"" << std::endl;
		throw "Errors in input file: cannot find \"width\"";
	}
	if (std::regex_match(data, match, std::regex(".*height\\s+(\\d+).*", std::regex_constants::icase)) && match.size() == 2) {
		height = std::stoi(match[1]);
		data = std::regex_replace(data, std::regex("height\\s+\\d+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"height\"" << std::endl;
		throw "Errors in input file: cannot find \"height\"";
	}
	if (std::regex_match(data, match, std::regex(".*car\\s+(\\d+).*", std::regex_constants::icase)) && match.size() == 2) {
		car = std::stoi(match[1]);
		data = std::regex_replace(data, std::regex("car\\s+\\d+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"car\"" << std::endl;
		throw "Errors in input file: cannot find \"car\"";
	}
	if (std::regex_match(data, match, std::regex(".*exit\\s+([a-z]+).*", std::regex_constants::icase)) && match.size() == 2) {
		std::string dir_str = match[1].str();
		if (dir_str == "left") { exit_direction = left; }
		else if (dir_str == "right") { exit_direction = right; }
		else if (dir_str == "up") { exit_direction = up; }
		else if (dir_str == "down") { exit_direction = down; }
		else { throw "unknown exit direction "; }
		data = std::regex_replace(data, std::regex("exit\\s+[a-z]+", std::regex_constants::icase), "");
	}
	else {
		std::cerr << "Errors in input file: cannot find \"exit\"" << std::endl;
		throw "Errors in input file: cannot find \"exit\"";
	}

	std::regex re_cell("(\\d+)");
	std::sregex_iterator cell_matches_begin = std::sregex_iterator(data.begin(), data.end(), re_cell);
	std::sregex_iterator cell_matches_end = std::sregex_iterator();

	if (std::distance(cell_matches_begin, cell_matches_end) == height*width) {
		unsigned * parking_lot_data = new unsigned[height*width];
		parking_lot = new unsigned*[height];
		for (unsigned i = 0; i<height; ++i) {
			parking_lot[i] = parking_lot_data + i*width;
		}
		unsigned pos = 0;
		for (std::sregex_iterator iter = cell_matches_begin; iter != cell_matches_end; ++iter) {
			parking_lot_data[pos++] = std::stoi((*iter).str());
		}
	}
	else {
		std::cerr << "Errors in input file: number of cells should be " << height << "*" << width << ". Found " << std::distance(cell_matches_begin, cell_matches_end) << std::endl;
		throw "Errors in input file: number of cells";
	}

	for (unsigned i = 0; i < height; i++)     // Going through the height of the board
	{ 
		for (unsigned j = 0; j < width; j++)  // Going through the width of the board
		{
			if (parking_lot[i][j] > 0)        // If there is a car, because the ID is there, and not a 0
			{
				Coordinates position;         // Create a coordinate object to store the positions
				position.x = j;               // Store the x position for the width
				position.y = i;				  // Store the y position for the height
				cars[parking_lot[i][j]].positions.push_back(position);  // Push back the position onto the cars map for the current car we're on
			}
		}
	}

	for (auto iter = cars.begin(); iter != cars.end(); iter++)                 // Going through the car map
	{
		if (iter->second.positions[0].y - iter->second.positions[1].y == 0)    // If two y coordinates next to each other have the same car ID, that car is horizontal
			iter->second.orientation = horisontal;
		else if (iter->second.positions[0].x - iter->second.positions[1].x == 0)  // If two x coordinates next to each other have the same car ID, that car is vertical
			iter->second.orientation = vertical;
	}
}

/******************************************************************************/
/*!
	\brief
		Makes a move on the board

	\param move
		A tuple that gives the car idea, direction to move, and number of spaces
		to move
*/
/******************************************************************************/
void ParkingLotSolver::makeMove(std::tuple< unsigned, Direction, unsigned > move)
{
	int d = std::get<1>(move); 
	int di = (d - 1)*((3 - d) % 2);    
	int dj = (d - 2)*(d % 2);       
	int scan_direction = di + dj;  

	unsigned num_positions = std::get<2>(move);
	unsigned car = std::get<0>(move);

	unsigned i_start = (scan_direction == 1) ? height - 1 : 0;
	unsigned j_start = (scan_direction == 1) ? width - 1 : 0;
	for (unsigned step = 0; step<num_positions; ++step) { 
		for (unsigned i = i_start; i<height; i -= scan_direction) {
			for (unsigned j = j_start; j<width; j -= scan_direction) {
				if (parking_lot[i][j] == car) {
					parking_lot[i][j] = 0;
					if (i + di >= height || j + dj >= width) {
						throw("Car moved outside of parking lot");
						return;
					}
					if (parking_lot[i + di][j + dj] > 0) {
						throw("Car moved on top of another car");
						return;
					}
					parking_lot[i + di][j + dj] = car;
				}
			}
		}
	}

	for (unsigned i = 0; i < cars[std::get<0>(move)].positions.size(); i++)
	{
		switch (std::get<1>(move))                                                // updating the cars position after it has been moved
		{
		case up: cars[std::get<0>(move)].positions[i].y -= std::get<2>(move);     // Decreasing y coordinate to go up
			break;
		case down: cars[std::get<0>(move)].positions[i].y += std::get<2>(move);   // Increasing y coordinate to go down
			break;
		case right: cars[std::get<0>(move)].positions[i].x += std::get<2>(move);  // Increasing x coordinate to go right
			break;
		case left: cars[std::get<0>(move)].positions[i].x -= std::get<2>(move);   // Decreasing x coordinate to go left
			break;
		case undefined:
			break;
		}
	}
}

/******************************************************************************/
/*!
	\brief
		Determines if the board was solved

	\return
		Returns if the board was solved
*/
/******************************************************************************/
bool ParkingLotSolver::IsSolved() const
{
	unsigned i_car_pos = height;
	unsigned j_car_pos = width;
	Orientation orientation = horisontal;
	bool done = false;
	for (unsigned i = 0; i<height && !done; ++i) {
		for (unsigned j = 0; j<width && !done; ++j) {
			if (parking_lot[i][j] == car) {
				if (i_car_pos == height) { // first time seeing car
					i_car_pos = i;
					j_car_pos = j;
				}
				else { //second time - ready to make decision 
					if (j_car_pos == j) { // default is horisontal
						orientation = vertical;
					}
					done = true;
				}
			}
		}
	}

	bool solved = false;
	switch (exit_direction) {
	case up:    solved = orientation == vertical   && parking_lot[0][j_car_pos] == car; break;
	case left:  solved = orientation == horisontal && parking_lot[i_car_pos][0] == car; break;
	case down:  solved = orientation == vertical   && parking_lot[height - 1][j_car_pos] == car; break;
	case right: solved = orientation == horisontal && parking_lot[i_car_pos][width - 1] == car; break;
	default: break;
	}
	return solved;
}

/******************************************************************************/
/*!
	\brief
		DFS function that solves the board

	\param solution
		A tuple of the solution

	\param history
		Vector that stores the history moves as tuples

	\param depth
		Depth of the search

	\param max_depth
		Max depth for the search to look at

	\return
		Returns if the board is solved
*/
/******************************************************************************/
bool ParkingLotSolver::Solve(std::vector<std::tuple< unsigned, Direction, unsigned> > & solution, std::set<std::vector<unsigned> > & history, unsigned depth, unsigned const & max_depth)
{
	if (IsSolved())                      // base case
		return true;

	if (depth >= max_depth)              // depth limit
		return false;

	std::vector< std::tuple<unsigned, Direction, unsigned> > possible_moves = PossibleMoves();   // Calling possible moves function, putting all possible moves in a vector of tuples

	for (std::tuple<unsigned, Direction, unsigned> const& m : possible_moves) {
		makeMove(m);								

		std::vector< unsigned > current_position;                        // Save to history
		for (unsigned k = 0; k < height * width; ++k) 
		{
			unsigned i = k / width;
			unsigned j = k % width;
			current_position.push_back(parking_lot[i][j]);
		}

		auto it_pos = history.find(current_position);                    // Check if already in history
		if (it_pos == history.end()) {                                   // If current position is not found
			auto it_insert = history.insert(current_position).first;     // Insert current position		                          
			if (Solve(solution, history, depth + 1, max_depth)) {        // Terminates when solution is found
				solution.push_back(m);
				return true;
			}

			history.erase(it_insert);									 // If here, no solution found, delete current position/board from history
		}

		std::tuple<unsigned, Direction, unsigned> undoMove;             // Create a tuple to hold the move to be undone

		switch (std::get<1>(m))                                                      // Undoing the move
		{
		case up: undoMove = std::make_tuple(std::get<0>(m), down, std::get<2>(m));   // Going down if we went up
			break;
		case down: undoMove = std::make_tuple(std::get<0>(m), up, std::get<2>(m));   // Going up if we went down
			break;
		case left: undoMove = std::make_tuple(std::get<0>(m), right, std::get<2>(m)); // Go right if we went left
			break;
		case right: undoMove = std::make_tuple(std::get<0>(m), left, std::get<2>(m)); // Go left if we went right
			break;
		case undefined: break;
		}

		makeMove(undoMove);															  // Undo the move
	}

	return false;
}

/******************************************************************************/
/*!
	\brief
		Determines all of the possible moves of a given board state

	\return
		Returns a vector of tuples of all of the possible moves
*/
/******************************************************************************/
std::vector< std::tuple<unsigned, Direction, unsigned> > ParkingLotSolver::PossibleMoves()
{
	std::vector< std::tuple<unsigned, Direction, unsigned> > possibleMoves;                               // Vector to store all of the possible moves
	
	for (auto iter = cars.begin(); iter != cars.end(); iter++)                                            // Walking through the vector of cars
	{
		if (iter->second.orientation == vertical)														  // If current car is vertical
		{
			// Starting at the top of the vertical car. Move keeps track of how many spaces the car can move
			for (int j = static_cast<int>(iter->second.positions[0].y), move = 1; j > 0; j--, move++)     // checking up
			{
				if (parking_lot[j - 1][iter->second.positions[0].x] == 0)                                 // If the square above is a 0 and the car can be moved up
				{
					std::tuple<unsigned, Direction, unsigned> possiblemove(iter->first, up, move);        // Create a tuple of that move
					possibleMoves.push_back(possiblemove);											      // Add the tuple to the vector of possible moves
				}	

				else
					break;
			}

			for (int j = static_cast<int>(iter->second.positions[iter->second.positions.size() - 1].y), move = 1; j < static_cast<int>(height); j++, move++)     // checking down
			{
				if (j == static_cast<int>(height) - 1)                         // If end of board has been reached, break out of the loop
					break;

				if (parking_lot[j + 1][iter->second.positions[0].x] == 0)     // If square below is a 0 and the car can be moved down
				{
					std::tuple<unsigned, Direction, unsigned> possiblemove(iter->first, down, move);   // Create a tuple of that move
					possibleMoves.push_back(possiblemove);											   // Add the tuple to the vector of possible moves
				}

				else
					break;
			}
		}

		else if (iter->second.orientation == horisontal)												  // If current car is horizontal
		{
			for (int j = static_cast<int>(iter->second.positions[0].x), move = 1; j > 0; j--, move++)     // checking left
			{
				if (parking_lot[iter->second.positions[0].y][j - 1] == 0)								  // If square to the left is 0 so car can be moved left
				{
					std::tuple<unsigned, Direction, unsigned> possiblemove(iter->first, left, move);      // Make a tuple of that move
					possibleMoves.push_back(possiblemove);
				}

				else
					break;
			}

			for (int j = static_cast<int>(iter->second.positions[iter->second.positions.size() - 1].x), move = 1; j < static_cast<int>(width); j++, move++)     // checking right
			{
				if (j == static_cast<int>(width) - 1)                            // If the right end of the board has been reached, break out of the loop
					break;
				if (parking_lot[iter->second.positions[0].y][j + 1] == 0)        // If the square to the right is a 0 and the car can be moved to the right
				{
					std::tuple<unsigned, Direction, unsigned> possiblemove(iter->first, right, move);    // Make a tuple of that move
					possibleMoves.push_back(possiblemove);
				}

				else
					break;
			}
		}
	}
	
	return possibleMoves;
}

/******************************************************************************/
/*!
	\brief
		Destructor
*/
/******************************************************************************/
ParkingLotSolver::~ParkingLotSolver()
{
	delete[] parking_lot[0];
	delete[] parking_lot;
}

/******************************************************************************/
/*!
	\brief
		Insertion operator

	\param os
		ostream

	\param d
		Direction

	\return
		Returns ostream object
*/
/******************************************************************************/
std::ostream& operator<<(std::ostream& os, Direction const& d) {
	switch (d) {
	case up:    os << "up "; break;
	case left:  os << "left "; break;
	case down:  os << "down "; break;
	case right: os << "right "; break;
	default:    os << "undefined"; break;
	}
	return os;
}

/******************************************************************************/
/*!
	\brief
		Insertion operator

	\param os
		ostream

	\param pl
		ParkingLotSolver object

	\return
		Returns ostream object
		
*/
/******************************************************************************/
std::ostream& operator <<(std::ostream& os, ParkingLotSolver const& pl) {
	for (unsigned i = 0; i<pl.height; ++i) {
		for (unsigned j = 0; j<pl.width; ++j) {
			os << pl.parking_lot[i][j] << " ";
		}
		os << std::endl;
	}
	return os;
}

/******************************************************************************/
/*!
	\brief
		Print function

	\param filename_out
		File to print to
*/
/******************************************************************************/
void ParkingLotSolver::Print(std::string const& filename_out)
{
	std::ofstream os;
	os.open(filename_out, std::ofstream::out | std::ofstream::app);
	for (unsigned i = 0; i<height; ++i) {
		for (unsigned j = 0; j<width; ++j) {
			os << parking_lot[i][j] << " ";
		}
	}
	os << std::endl;
}
