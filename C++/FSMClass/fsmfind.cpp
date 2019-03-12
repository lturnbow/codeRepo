/******************************************************************************/
/*!
\file   fsmfind.cpp
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS225
\par    Assignment 5
\date   11/30/2016
*/
/******************************************************************************/
#include "fsmfind.h"
#include <set>

namespace CS225 {
	template <typename Symbol>
	FSMFind<Symbol>::FSMFind(const std::vector<Symbol>& _pattern) : pattern(_pattern)
	{
		// Create an iterator to go through the pattern
		typename std::vector<Symbol>::const_iterator iter = pattern.begin();
		// Create a new vector to hold the initial state
		std::vector<Symbol> state;

		// Push back the initial state onto the vector of vector states
		states.push_back(new State<Symbol>(state));

		// Going through the pattern
		while (iter != pattern.end()) {
			state.push_back(*iter);                   // Push back each iterator into a state

													  // If at the end of the pattern, push back the vector onto states and set is terminal
													  //to true
			if (pattern.size() == state.size()) {
				states.push_back(new State<Symbol>(state, true, *states.begin()));
				break;
			}

			// If not at the end of the pattern, push back the vector onto states and set is terminal to true
			states.push_back(new State<Symbol>(state, false, *states.begin()));
			iter++;
		}

		CreateTransitions();
	}

	// main functionality
	template <typename Symbol>
	void FSMFind<Symbol>::Find(const std::vector<Symbol> & text)
	{
		// State pointer
		const State<Symbol>* statePt = (*(states.begin()));
		int pos = 0;

		typename std::vector<Symbol>::const_iterator iter = text.begin();
		while (iter != text.end())         // Going through the text to find the pattern
		{
			statePt = statePt->NextState(*iter);   // Move through states

			if (statePt->IsTerminal())     // If the end of the pattern is reached
			{
				// If a pattern is found, add position into vecOnFind vector
				std::vector<AbstractCallback*>::const_iterator ACiter = vecOnFind.begin();
				while (ACiter != vecOnFind.end())
				{
					(*ACiter)->OnFind(pos);
					ACiter++;
				}
			}

			pos++;
			iter++;
		}

		// If finished going through text, say we're done
		std::vector<AbstractCallback*>::const_iterator ACiter = vecOnDone.begin();
		while (ACiter != vecOnDone.end())
		{
			(*ACiter)->OnDone();
			ACiter++;
		}
	}

	template <typename Symbol>
	std::vector<Symbol> FSMFind<Symbol>::substring(const std::vector<Symbol> & str, size_t pos) const
	{
		// Subtracts from the beginning of a string
		return std::vector<Symbol>(str.begin() + pos, str.end());
	}

	// preprocessing - called in the end of constructor
	template <typename Symbol>
	void FSMFind<Symbol>::CreateTransitions()
	{
		std::set<Symbol> set;                         // Set to hold individual characters in the pattern
		typename std::set<Symbol>::iterator set_iter = set.begin();
		typename std::vector<Symbol>::const_iterator pattern_iter = pattern.begin();

		// Filling set with pattern, no duplicate characters
		for (pattern_iter = pattern.begin(); pattern_iter != pattern.end(); pattern_iter++)
			set.insert(*pattern_iter);

		typename std::vector<State<Symbol>*>::const_iterator states_iter = states.begin();

		for (states_iter = states.begin(); states_iter != states.end(); states_iter++)
		{
			for (set_iter = set.begin(); set_iter != set.end(); set_iter++)
			{
				// Vector that will store the state names
				std::vector<Symbol> buffer = (*states_iter)->Name();
				// Each individual characcter 
				buffer.push_back(*set_iter);

				// Don't go past end of array and if the next state equals what's currently in the buffer
				// Move to the next state by adding a transition
				if ((states_iter + 1) != states.end() && buffer == (*(states_iter + 1))->Name())
					(*states_iter)->AddTransition(*set_iter, *(states_iter + 1));

				else
				{
					// Start at where the iterator is at currently and go backards
					typename std::vector<State<Symbol>*>::const_iterator back_iter;
					back_iter = states_iter;
					while (back_iter != states.begin())
					{
						buffer = substring(buffer, 1);
						// If transition is found going back through the pattern
						if (buffer == (*back_iter)->Name())
						{
							// Move to that state
							(*states_iter)->AddTransition(*set_iter, *back_iter);
							break;
						}

						back_iter--;
					}
				}
			}
		}
	}

	// client registers handlers
	template <typename Symbol>
	void FSMFind<Symbol>::RegisterOnFind(AbstractCallback* p_cb)
	{
		vecOnFind.push_back(p_cb);
	}

	template <typename Symbol>
	void FSMFind<Symbol>::RegisterOnDone(AbstractCallback* p_cb)
	{
		vecOnDone.push_back(p_cb);
	}

	template <typename Symbol>
	FSMFind<Symbol>::~FSMFind()
	{
		// Going through the states, delete each vector
		typename std::vector<State<Symbol>*>::const_iterator iter;
		for (iter = states.begin(); iter != states.end(); ++iter)
			delete *iter;
	}
}



