#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include <AbstractMaterialColor.h>
#include <memory>
#include <Vector3.h>
#include <Vector4.h>

namespace K9 {
	struct HitRecord {
		using Color = AbstractMaterialColor::Color;
		HitRecord(const AbstractMaterialColor &ka, const AbstractMaterialColor &kd, const AbstractMaterialColor &ks, float p, const AbstractMaterialColor &km, float t, Vector4 n) :
			ka(ka.clone()),
			kd(kd.clone()),
			ks(ks.clone()),
			p(p),
			km(km.clone()),
			t(t),
			n(n) {
		}

		std::shared_ptr<AbstractMaterialColor> ka;
		std::shared_ptr<AbstractMaterialColor> kd;
		std::shared_ptr<AbstractMaterialColor> ks;
		float p;
		std::shared_ptr<AbstractMaterialColor> km;
		float t;
		Vector4 n;
	};
}

#endif // !_HITRECORD_H_
