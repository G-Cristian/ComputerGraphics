#ifndef _POINT2D_H_
#define _POINT2D_H_

namespace Geometry {
	class Point2D {
	public:
		Point2D(double x, double y) {
			this->x = x;
			this->y = y;
		}
		~Point2D() {

		}

		Point2D operator+(const Point2D &other) const {
			return Point2D(x + other.x, y + other.y);
		}

		Point2D operator-() const {
			return Point2D(-x, -y);
		}

		Point2D operator-(const Point2D &other) const {
			return *this + (-other);
		}

		Point2D operator*(double n) const{
			return Point2D(x*n, y*n);
		}

		Point2D operator/(double n) const {
			return Point2D(x/n, y/n);
		}

		double x;
		double y;
	};

	Point2D operator*(double n, const Point2D &p);
}

#endif

