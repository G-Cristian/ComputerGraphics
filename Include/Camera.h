#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Vector3.h>

namespace K9 {

	class Camera {
	public:

	protected:
		Camera(const Vector3 &position, const Vector3 &up, const Vector3 &direction) :
			Camera(position, up, direction, -direction) {
		}
		Camera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const Vector3 &w) {
			//TODO
		}

		Vector3 _position;
		Vector3 _v;
		Vector3 _u;
		Vector3 _w;
		Vector3 _direction;
	};

}

#endif // !_CAMERA_H_
