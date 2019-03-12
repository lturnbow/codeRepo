/******************************************************************************/
/*!
\file   fsmfind.h
\author Lauren Turnbow
*/
/******************************************************************************/
#ifndef FSMFIND_H
#define FSMFIND_H
#include <vector>
#include "abstract-callback.h"

namespace CS225 {
	template <typename Symbol>
	class FSMFind {
	public:
		FSMFind( const std::vector<Symbol>& _pattern); 
		~FSMFind();
        // client registers handlers
		void RegisterOnFind(AbstractCallback* p_cb);
		void RegisterOnDone(AbstractCallback* p_cb);
        // main functionality
		void Find(const std::vector<Symbol> & text);
	private:
		FSMFind(const FSMFind&); // do not implement in fsmfind.cpp
		FSMFind& operator=(const FSMFind&); // do not implement in fsmfind.cpp
		std::vector<Symbol> 
			substring(const std::vector<Symbol> & str, size_t pos) const;
		void CreateTransitions();
	private:
		std::vector<Symbol> const      pattern;
		std::vector<State<Symbol>*>    states;
		std::vector<AbstractCallback*> vecOnFind;
		std::vector<AbstractCallback*> vecOnDone;
	};
}
#include "fsmfind.cpp"
#endif
