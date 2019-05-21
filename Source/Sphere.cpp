#include <algorithm>
#include <MathUtility.h>
#include <memory>
#include <Sphere.h>

namespace K9 {
	bool Sphere::hit(const Ray &ray, float t0, float t1, std::unique_ptr<HitRecord> &outHitRecord) const {
		outHitRecord.reset(nullptr);
		float a = dot(ray.direction(), ray.direction());
		float b = 2* dot(ray.direction(), (ray.origin() - _center));
		float c = dot((ray.origin() - _center), (ray.origin() - _center)) - (_radius * _radius);
		float x1 = 0.0f;
		float x2 = 0.0f;
		bool hit = (MathUtility::solveQuadraticEquation(a, b, c, x1, x2) > 0);
		if (hit) {
			float minHit = std::min(x1, x2);
			hit = (t0 <= minHit && minHit <= t1);
			if (hit) {
				outHitRecord.reset(	new HitRecord(	*_material.ambientCoefficient(),
													*_material.diffuseCoefficient(),
													*_material.specularCoefficient(),
													_material.phongExponent(),
													*_material.mirrorReflection(),
													minHit,
													((ray.origin() + minHit*ray.direction()) - _center) / _radius
												)
								);
			}
		}

		return hit;
	}
}