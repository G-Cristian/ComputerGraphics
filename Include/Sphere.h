#ifndef _SPHERE_H_
#define _SPHERE_H_

#include <HitRecord.h>
#include <Ray.h>
#include <Surface.h>
#include <Vector3.h>

namespace K9 {
	class Sphere :public Surface {
	public:
		Sphere(const Vector3 &center, float radius, const Material &material) :
			Surface(material),
			_center(center),
			_radius(radius){
		}
		~Sphere() {}

		bool hit(const Ray &ray, float t0, float t1, HitRecord &outHitRecord) const override final;
	private:
		Vector3 _center;
		float _radius;
	};
}

#endif // !_SPHERE_H_
