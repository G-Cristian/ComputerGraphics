#include <BoxFilter.h>

namespace K9 {
	float BoxFilter::execute(float x) const {
		if (-_radius <= x && x < _radius) {
			return 1 / (2 * _radius);
		}
		else
		{
			return 0.0f;
		}
	}
}