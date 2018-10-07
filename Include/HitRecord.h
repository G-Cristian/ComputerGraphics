#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include <Vector3.h>

namespace K9 {
	typedef Vector3 Color;
	struct HitRecord {
		HitRecord(const Color &ka, const Color &kd, const Color &ks, float p, const Color &km, float t, Vector3 n) :
			ka(ka),
			kd(kd),
			ks(ks),
			p(p),
			km(km),
			t(t),
			n(n) {
		}

		Color ka;
		Color kd;
		Color ks;
		float p;
		Color km;
		float t;
		Vector3 n;
	};
}

#endif // !_HITRECORD_H_
