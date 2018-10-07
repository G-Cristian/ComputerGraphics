#ifndef _PERSPECTIVECAMERA_H_
#define _PERSPECTIVECAMERA_H_

#include <Camera.h>

namespace K9 {

	class PerspectiveCamera :public Camera {
	public:
		PerspectiveCamera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const ImagePlane &imagePlane, float imagePlaneDistance) :
			PerspectiveCamera(position, up, direction, -direction, imagePlane, imagePlaneDistance) {
		}

		PerspectiveCamera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const Vector3 &w, const ImagePlane &imagePlane, float imagePlaneDistance) :
			Camera(position, up, direction, w, imagePlane),
			_imagePlaneDistance(imagePlaneDistance){
		}

		PerspectiveCamera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const float angle, float imagePlaneDistance) :
			PerspectiveCamera(position, up, direction, -direction, angle, imagePlaneDistance) {
		}

		PerspectiveCamera(const Vector3 &position, const Vector3 &up, const Vector3 &direction, const Vector3 &w, const float angle, float imagePlaneDistance) :
			PerspectiveCamera(position, up, direction, w, ImagePlane(), imagePlaneDistance) {

			float hipo = _w.norm()*_imagePlaneDistance / cosf(angle);
			float side = sinf(angle)* hipo;
			float side_2 = side / 2.0f;
			_imagePlane.left = -side_2;
			_imagePlane.bottom = -side_2;
			_imagePlane.width = side;
			_imagePlane.height = side;
		}

		float imagePlaneDistance() const { return _imagePlaneDistance; }

		Ray calculateRay(int px, int py, int width, int height) const override final {
			float u = _imagePlane.left + (_imagePlane.width)*(px + 0.5f) / width;
			float v = _imagePlane.bottom + (_imagePlane.height)*(py + 0.5f) / height;

			return Ray(_position, normalized(_imagePlaneDistance*_direction + u*_u + v*_v));
		}

	private:
		float _imagePlaneDistance;			///imagePlaneDistance (focal length)
	};

}

#endif // !_PERSPECTIVECAMERA_H_
