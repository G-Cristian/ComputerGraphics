#ifndef _SHARPFILTER_H_
#define _SHARPFILTER_H_

#include <Filter.h>

namespace K9 {
	class SharpFilter :public Filter {
	public:
		SharpFilter(float alpha, float sigma = 1.0f, float radius = 2.0f) :
			Filter(radius),
			_sigma(sigma),
			_alpha(alpha){
		}
		virtual ~SharpFilter() {}

		float execute(float x) const override final;
	private:
		float _sigma;
		float _alpha;
	};
}

#endif // !_SHARPFILTER_H_
