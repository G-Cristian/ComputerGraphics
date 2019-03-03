#include <BoxFilter.h>

namespace K9 {
	float BoxFilter::execute(float x) const {
		if (-1 <= _radius && _radius < 1) {
			return 1 / (2 * _radius);
		}
		else
		{
			return 0.0f;
		}
	}
}