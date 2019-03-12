#ifndef WORDER_H
#define WORDER_H

#include <string>
#include <vector>
#include <list>

namespace CS225 {
	typedef std::list<std::string>   StringList;
	typedef std::vector<std::string> StringVec;

	class Worder {
		public:
			Worder();
			bool Load( std::string const& filename );
			void Print( bool oneline = true ) const;
			unsigned CharCount() const;
			StringList WordsOfLength( unsigned length ) const;
			StringList FindDuplicates() const;
			unsigned StartsWith( std::string const& prefix ) const;
			unsigned Substrings( std::string const& substring ) const;
			void RemoveAll( std::string const& word );
			void UpperCase();
			void ReverseLetters();
			StringList CommonWords( Worder const& rhs) const;
			StringList JoinWords( Worder const& rhs) const;

		private:
			StringVec words_;
	};

}

#endif
