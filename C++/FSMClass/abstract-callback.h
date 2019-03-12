#ifndef ABSTRACTCALLBACK_H
#define ABSTRACTCALLBACK_H


namespace CS225 {
	class AbstractCallback {
		public:
			virtual void OnFind(size_t pos) = 0;
			virtual void OnDone() = 0;
			virtual ~AbstractCallback() {}
	};
}
#endif
