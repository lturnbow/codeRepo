/******************************************************************************/
/*!
\file   state.h
\author Lauren Turnbow
*/
/******************************************************************************/
#ifndef STATE_H
#define STATE_H
#include <vector>
#include <map>

namespace CS225 {
	template <typename Symbol>
	class State {
		public:
			State(const std::vector<Symbol>& _name);
			State(  const std::vector<Symbol>& _name, 
					bool _isTerminal, 
					const State* p_default_target); 
			void AddTransition(const Symbol & sym, const State * p_target);
			const State* NextState(const Symbol & sym) const;
			void PrintDebug() const;
			std::vector<Symbol> Name() const;
			bool IsTerminal() const;
		private:
			void Print(const std::vector<Symbol> & v) const;
			std::vector<Symbol> name;   // human readable name of the state, use prefix itself
			bool isTerminal;            // is the goal state?
			std::map<Symbol,const State<Symbol>*> transitions;  //transitions for all symbols in the pattern
			State<Symbol> const * p_default_state;
	};

}
#include "state.cpp"
#endif
