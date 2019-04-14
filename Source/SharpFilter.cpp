#include <GaussianFilter.h>
#include <MathUtility.h>
#include <SharpFilter.h>

namespace K9 {
	float SharpFilter::execute(float x) const {
		GaussianFilter gaussianFilter(_sigma, _radius);
		float gaussianTimesAlpha = _alpha * gaussianFilter.execute(x);
		return (FLOAT_EQ(0.0f,x, E_1_100000))? ((1 + _alpha) - gaussianTimesAlpha) : (gaussianTimesAlpha);
	}
}