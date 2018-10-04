#include <algorithm>
#include <MathUtility.h>
#include <Sphere.h>

namespace K9 {
	bool Sphere::hit(const Ray &ray, float t0, float t1, HitRecord &outHitRecord) const {
		float a = ray.direction() * ray.direction();
		float b = 2*ray.direction()*(ray.origin() - _center);
		float c = (ray.origin() - _center)*(ray.origin() - _center) - (_radius * _radius);
		float x1 = 0.0f;
		float x2 = 0.0f;
		bool hit = MathUtility::solveQuadraticEquation(a, b, c, x1, x2);
		if (hit) {
			float minHit = std::min(x1, x2);
			hit = (t0 <= minHit && minHit <= t1);
			if (hit) {
				outHitRecord.t = minHit;
				outHitRecord.n = ((ray.origin() + minHit*ray.direction()) - _center) / _radius;
			}
		}

		return hit;
	}
}