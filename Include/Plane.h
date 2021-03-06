#ifndef _PLANE_H_
#define _PLANE_H_

#include <HitRecord.h>
#include <Material.h>
#include <Surface.h>
#include <Vector3.h>

namespace K9 {

	class Plane :public Surface {
	public:
		Plane(const Vector4 &point, const Vector4 &normal, const Material &material):
			Surface(material),
			_a(point),
			_n(normal){
			_n.normalize();
		}

		bool hit(const Ray &ray, float t0, float t1, std::unique_ptr<HitRecord> &outHitRecord) const override final;

		~Plane() {}
	private:
		Vector4 _a;
		Vector4 _n;
	};

}

#endif // !_PLANE_H_
