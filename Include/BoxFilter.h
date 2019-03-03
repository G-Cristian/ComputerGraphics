#ifndef _BOXFILTER_H_
#define _BOXFILTER_H_

#include <Filter.h>

namespace K9 {
	class BoxFilter:public Filter {
	public:
		BoxFilter(float radius = 0.5f):
			Filter(radius) {
		}
		virtual ~BoxFilter() {}
		float execute(float x) const override final;
	};
}

#endif // !_BOXFILTER_H_
