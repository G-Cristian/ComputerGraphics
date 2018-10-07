#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include <algorithm>

namespace K9 {

	class Vector3 {
	public:
		Vector3(float x, float y, float z) {
			_vectorImp.x = x;
			_vectorImp.y = y;
			_vectorImp.z = z;
		}

		Vector3(const Vector3 &other) {
			memcpy((void*)_vectorImp.vec, (void*)other._vectorImp.vec, 3 * sizeof(float));
		}

		~Vector3() {}

		//access operators
		float operator[](int i) const { return _vectorImp.vec[i]; }
		float& operator[](int i) { return _vectorImp.vec[i]; }

		//operators
		Vector3& operator=(const Vector3 &other) {
			memcpy((void*)_vectorImp.vec, (void*)other._vectorImp.vec, 3 * sizeof(float));

			return *this;
		}

		//aritmetic operators
		Vector3 operator+(const Vector3 &other) const;
		Vector3 operator-() const;
		Vector3 operator-(const Vector3 &other) const;
		float operator*(const Vector3 &other) const;
		Vector3 operator*(float scalar) const;
		Vector3 operator/(float scalar) const;
		friend Vector3 operator*(float scalar, const Vector3 &vector);

		//other vector operations
		float norm() const;
		Vector3& normalize();
		friend Vector3 cross(const Vector3 &v1, const Vector3 &v2);
		friend Vector3 perElementProduct(const Vector3 &v1, const Vector3 &v2);
		bool isZero() const { return _vectorImp.x == 0.0f && _vectorImp.y == 0.0f && _vectorImp.z == 0.0f; }

		//helpers
		friend void swap(Vector3 &v1, Vector3 &v2);
	private:
		union Vector3Imp {
			struct {
				float x;
				float y;
				float z;
			};

			float vec[3];
		};

		Vector3Imp _vectorImp;
	};

	//friend functions
	Vector3 operator*(float scalar, const Vector3 &vector);

	//other functions
	inline Vector3 normalized(const Vector3 &vector);
	inline Vector3 cross(const Vector3 &v1, const Vector3 &v2);
	inline Vector3 perElementProduct(const Vector3 &v1, const Vector3 &v2);
	
	inline void swap(Vector3 &v1, Vector3 &v2);
}

#include "../Source/Vector3.cpp"

#endif // !_VECTOR3_H_
