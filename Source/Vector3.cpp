//my includes
#include <Vector3.h>

//other includes
#include <math.h>

namespace K9 {

	inline Vector3 Vector3::operator+(const Vector3 &other) const {
		return Vector3(_vectorImp.x + other._vectorImp.x, _vectorImp.y + other._vectorImp.y, _vectorImp.z + other._vectorImp.z);
	}

	inline Vector3 Vector3::operator-() const {
		return *this * (-1);
	}

	inline Vector3 Vector3::operator-(const Vector3 &other) const {
		return *this + (-other);
	}

	inline float Vector3::operator*(const Vector3 &other) const {
		return _vectorImp.x * other._vectorImp.x + _vectorImp.y * other._vectorImp.y + _vectorImp.z * other._vectorImp.z;
	}

	inline Vector3 Vector3::operator*(float scalar) const {
		return Vector3(_vectorImp.x * scalar, _vectorImp.y * scalar, _vectorImp.z * scalar);
	}

	inline Vector3 Vector3::operator/(float scalar) const {
		return Vector3(_vectorImp.x / scalar, _vectorImp.y / scalar, _vectorImp.z / scalar);
	}

	inline Vector3 operator*(float scalar, const Vector3 &vector) {
		return vector*scalar;
	}

	inline float Vector3::norm() const {
		return sqrtf((*this) * (*this));
	}

	inline Vector3& Vector3::normalize() {
		float n = this->norm();
		*this = *this / n;

		return *this;
	}

	inline Vector3 normalized(const Vector3 &vector) {
		Vector3 vec(vector);
		vec.normalize();
		return vec;
	}

	inline Vector3 cross(const Vector3 &v1, const Vector3 &v2) {
		return Vector3(	v1._vectorImp.y * v2._vectorImp.z - v2._vectorImp.y * v1._vectorImp.z,
						v1._vectorImp.z * v2._vectorImp.x - v2._vectorImp.z * v1._vectorImp.x,
						v1._vectorImp.x * v2._vectorImp.y - v2._vectorImp.x * v1._vectorImp.y);
	}

	inline Vector3 perElementProduct(const Vector3 &v1, const Vector3 &v2) {
		return Vector3(v1._vectorImp.x * v2._vectorImp.x, v1._vectorImp.y * v2._vectorImp.y, v1._vectorImp.z * v2._vectorImp.z);
	}

	inline void swap(Vector3 &v1, Vector3 &v2) {
		using std::swap;
		swap(v1._vectorImp.vec, v2._vectorImp.vec);
	}
}