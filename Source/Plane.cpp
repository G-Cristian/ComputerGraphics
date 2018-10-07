#include <HitRecord.h>
#include <MathUtility.h>
#include <Plane.h>
#include <Vector3.h>

namespace K9 {

	bool Plane::hit(const Ray &ray, float t0, float t1, std::unique_ptr<HitRecord> &outHitRecord) const {
		bool hit = false;
		outHitRecord.reset(nullptr);

		float dn = normalized(ray.direction()) *_n;

		if (ray.direction()[1] > 0) {
			int a = 3;
			a++;
		}


		if (dn < 0.0f) {
			float t = ((_a - ray.origin()) * _n) / dn;
			hit = t0 <= t && t <= t1;
			if (hit) {
				outHitRecord.reset(	new HitRecord(	_material.ambientCoefficient(),
													_material.diffuseCoefficient(),
													_material.specularCoefficient(),
													_material.phongExponent(),
													_material.mirrorReflection(),
													t,
													_n
												 )
								  );
			}
		}

		return hit;
	}

}