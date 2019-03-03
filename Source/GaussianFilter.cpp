#define _USE_MATH_DEFINES
#include <GaussianFilter.h>
#include <math.h>


namespace K9 {
	float GaussianFilter::execute(float x) const {
		return powf(M_E, -(x*x) / (2.0f*_sigma*_sigma)) / (_sigma*sqrtf(2.0f*M_PI));
	}
}