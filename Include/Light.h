#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <Vector3.h>

namespace K9 {

	class Light {
	public:
		Light(const Vector3 &position, const Vector3 &intensity) :
			_position(position),
			_intensity(intensity) {
		}

		const Vector3& position() const { return _position; }
		Vector3& position() { return _position; }
		const Vector3& intensity() const { return _intensity; }
		Vector3& intensity() { return _intensity; }
	private:
		Vector3 _position;
		Vector3 _intensity;
	};

}

#endif // !_LIGHT_H_
