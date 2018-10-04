#ifndef _SURFACE_H_
#define _SURFACE_H_

//my includes
#include <HitRecord.h>
#include <Material.h>
#include <Ray.h>

namespace K9 {
	class Surface {
	public:
		~Surface() = default;
		virtual bool hit(const Ray &ray, float t0, float t1, HitRecord &outHitRecord) const = 0;

		//getters
		const Material& material() const { return _material; }
		Material& material() { return _material; }

	protected:
		Surface(const Material &material):
			_material(material){
		}
		Surface(const Surface &other) = default;
		Surface& operator=(const Surface &other) = default;

		Material _material;
	};
}

#endif // !_SURFACE_H_
