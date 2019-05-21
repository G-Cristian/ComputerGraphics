#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Vector3.h>
#include <Vector4.h>

namespace K9 {

	class Light {
	public:
		Light(const Vector3 &position, const Vector4 &intensity) :
			_position(position),
			_intensity(intensity) {
		}

		Light(const Vector3 &position, const Vector3 &intensity) :
			_position(position),
			_intensity(intensity, 1.0f) {
		}

		const Vector3& position() const { return _position; }
		Vector3& position() { return _position; }
		const Vector4& intensity() const { return _intensity; }
		Vector4& intensity() { return _intensity; }
	private:
		Vector3 _position;
		Vector4 _intensity;
	};

}

#endif // !_LIGHT_H_
