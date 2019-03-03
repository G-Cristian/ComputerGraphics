#ifndef _GAUSSIANFILTER_H_
#define _GAUSSIANFILTER_H_

#include <Filter.h>

namespace K9 {
	class GaussianFilter :public Filter {
	public:
		GaussianFilter(float sigma = 1.0f, float radius = 2.0f) :
			Filter(radius),
			_sigma(sigma) {
		}
		virtual ~GaussianFilter() {}

		float execute(float x) const override final;
	private:
		float _sigma;
	};
}

#endif // !_GAUSSIANFILTER_H_
