#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <Ray.h>
#include <Vector3.h>

namespace K9 {

	class Camera {
	public:
		virtual ~Camera() {}

		struct ImagePlane {
			float left;
			float bottom;
			float width;
			float height;
		};

		const Vector3& position() const { return _position; }
		const Vector3& direction() const { return _direction; }
		const Vector3& u() const { return _u; }
		const Vector3& v() const { return _v; }
		const Vector3& w() const { return _w; }
		const ImagePlane& imagePlane() const { return _imagePlane; }

		virtual Ray calculateRay(int px, int py, int width, int height) const = 0;

	protected:
		Camera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const ImagePlane &imagePlane) :
			Camera(position, up, direction, -direction, imagePlane) {
		}
		Camera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const Vector3 &w, const ImagePlane &imagePlane) :
			_position(position),
			_u(cross(up,w)),
			_w(w),
			_v(cross(w, cross(up, w))),
			_direction(direction),
			_imagePlane(imagePlane) {
			_v.normalize();
			_u.normalize();
			_w.normalize();
			_direction.normalize();
		}

		Vector3 _position;
		Vector3 _v;
		Vector3 _u;
		Vector3 _w;
		Vector3 _direction;
		ImagePlane _imagePlane;
	};

}

#endif // !_CAMERA_H_
