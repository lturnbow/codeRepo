/******************************************************************************/
/*!
\file   state.cpp
\author Lauren Turnbow
\par    email: lauren.turnbow\@digipen.edu
\par    DigiPen login: lauren.turnbow
\par    Course: CS225
\par    Assignment 5
\date   11/30/2016
*/
/******************************************************************************/

#include "state.h"
namespace CS225 {
	//ctor for the initial node - default transition is to self name is 
	template <typename Symbol>
	State<Symbol>::State(const std::vector<Symbol>& _name) : name(_name)
	{
		isTerminal = false;      // default not at the end of the pattern
		p_default_state = this;
	}

	//ctor for non-initial nodes, default transition should be set to the initial node - provided by the user.
	template <typename Symbol>
	State<Symbol>::State(const std::vector<Symbol>& _name, bool _isTerminal, const State* p_default_target) 
		: name(_name), isTerminal(_isTerminal), p_default_state(p_default_target) {}

	template <typename Symbol>
	void State<Symbol>::AddTransition(const Symbol & sym, const State * p_target)
	{
		// inserting into transitions
		transitions.insert(std::make_pair<Symbol, const State<Symbol>*>(sym, p_target));
	}

	template <typename Symbol>
	const State<Symbol>* State<Symbol>::NextState(const Symbol & sym) const
	{
		// Decides what state to go to next
		typename std::map<Symbol, const State<Symbol>*>::const_iterator iter = transitions.find(sym);
		if (iter == transitions.end())
			return p_default_state;
		else
			return iter->second;
	}

	template <typename Symbol>
	std::vector<Symbol> State<Symbol>::Name() const {
		return name;
	}

	// check if at the end of the pattern
	template <typename Symbol>
	bool State<Symbol>::IsTerminal() const {
		return isTerminal;
	}

	template <typename Symbol>
	void State<Symbol>::Print(const std::vector<Symbol> & v) const
	{
		typename std::vector<Symbol>::iterator iter;
		// Print each symbol in the vector
		for (iter = v.begin(); iter != v.end(); iter++)
			std::cout << (*iter);
		std::cout << '\n';
	}

	template <typename Symbol>
	void State<Symbol>::PrintDebug() const { }
}

