#ifndef _RAY_H_
#define _RAY_H_

//my includes
#include <Vector3.h>
#include <Vector4.h>

//other includes
#include <algorithm>

namespace K9 {

	class Ray {
	public:
		Ray(const Vector4 &origin, const Vector4 &direction) :
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
		const Vector4& origin() const		{ return _origin; }
		Vector4& origin()					{ return _origin; }
		const Vector4& direction() const	{ return _direction; }
		Vector4& direction()				{ return _direction; }

		//helpers
		friend void swap(Ray &r1, Ray &r2);
	private:
		Vector4 _origin;
		Vector4 _direction;
	};

	inline void swap(Ray &r1, Ray &r2) {
		using std::swap;
		swap(r1._origin, r2._origin);
		swap(r1._direction, r2._direction);
	}
}

#endif // !_RAY_H_
