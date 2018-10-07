#include "../Include/Point2D.h"

namespace Geometry {
	Point2D operator*(double n, const Point2D &p) {
		return p*n;
	}
}