#ifndef _HITRECORD_H_
#define _HITRECORD_H_

#include <Vector3.h>

namespace K9 {
	struct HitRecord {
		float ka;
		float kd;
		float ks;
		float t;
		Vector3 n;
	};
}

#endif // !_HITRECORD_H_
