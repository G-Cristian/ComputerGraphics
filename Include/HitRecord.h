#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include <Vector3.h>

namespace K9 {
	typedef Vector3 Color;
	struct HitRecord {
		Color ka;
		Color kd;
		Color ks;
		float p;
		float t;
		Vector3 n;
	};
}

#endif // !_HITRECORD_H_
