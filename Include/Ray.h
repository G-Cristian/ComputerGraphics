#ifndef _RAY_H_
#define _RAY_H_

//my includes
#include <Vector3.h>

//other includes
#include <algorithm>

namespace K9 {

	class Ray {
	public:
		Ray(const Vector3 &origin, const Vector3 &direction) :
			_origin(origin),
			_direction(direction)
		{}
		~Ray() {}

		//operators
		Ray& operator=(const Ray &other) {
			Ray aux(other);
			swap(*this, aux);

			return *this;
		}

		//member accesors
		const Vector3& origin() const		{ return _origin; }
		Vector3& origin()					{ return _origin; }
		const Vector3& direction() const	{ return _direction; }
		Vector3& direction()				{ return _direction; }

		//helpers
		friend void swap(Ray &r1, Ray &r2);
	private:
		Vector3 _origin;
		Vector3 _direction;
	};

	inline void swap(Ray &r1, Ray &r2) {
		using std::swap;
		swap(r1._origin, r2._origin);
		swap(r1._direction, r2._direction);
	}
}

#endif // !_RAY_H_
