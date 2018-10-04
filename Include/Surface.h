#ifndef _SURFACE_H_
#define _SURFACE_H_

//my includes
#include <HitRecord.h>
#include <Ray.h>

namespace K9 {
	class Surface {
	public:
		~Surface() = default;
		virtual bool hit(const Ray &ray, float t0, float t1, HitRecord &outHitRecord) const = 0;
	protected:
		Surface() = default;
		Surface(const Surface &other) = default;
		Surface& operator=(const Surface &other) = default;
	};
}

#endif // !_SURFACE_H_
