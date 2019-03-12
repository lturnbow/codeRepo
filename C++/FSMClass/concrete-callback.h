#ifndef CONCRETECALLBACK_H
#define CONCRETECALLBACK_H
#include "abstract-callback.h"
#include <vector>

namespace CS225 {

    class ConcreteCallback1 : public AbstractCallback {
		public:
			void OnFind(size_t pos);
			void OnDone();
	};

	template <typename Symbol>
		class ConcreteCallback2 : public AbstractCallback {
			public:
				ConcreteCallback2(const std::vector<Symbol> & _pattern);
				void OnFind(size_t pos);
				void OnDone();
			private:
				const std::vector<Symbol> pattern;
				size_t count;
				void Print(const std::vector<Symbol> & v);
		};

}
#include "concrete-callback.cpp"
#endif
