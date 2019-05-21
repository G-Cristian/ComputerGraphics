#ifndef _VECTOR4_H_
#define _VECTOR4_H_

#include <assert.h>
#include <iostream>
#include <math.h>
#include <string>
#include <Vector3.h>

namespace K9 {
	class Vector4 {
		typedef float ElementsType;
	public:
		Vector4() :
			Vector4(0.0f, 0.0f, 0.0f, 0.0f) {
		}
		Vector4(ElementsType fillValue) {
			_vectorImp.x = fillValue;
			_vectorImp.y = fillValue;
			_vectorImp.z = fillValue;
			_vectorImp.w = fillValue;
			//std::cout << "Vector4 constructor 1" << std::endl;
		}
		Vector4(ElementsType x, ElementsType y, ElementsType z, ElementsType w=ElementsType()) {
			_vectorImp.x = x;
			_vectorImp.y = y;
			_vectorImp.z = z;
			_vectorImp.w = w;
			//std::cout << "Vector4 constructor 1" << std::endl;
		}

		Vector4(ElementsType vec[4]) {
			memcpy((void*)(_vectorImp.vec), (void*)(vec), 4 * sizeof(ElementsType));
		//	std::cout << "Vector4 constructor 2" << std::endl;
		}

		Vector4(Vector3 xyz, ElementsType w=ElementsType()) {
			_vectorImp.x = xyz[0];
			_vectorImp.y = xyz[1];
			_vectorImp.z = xyz[2];
			_vectorImp.w = w;
			//std::cout << "Vector4 constructor 1" << std::endl;
		}

		Vector4(const Vector4 &other):
			_vectorImp(other._vectorImp) {
			//std::cout << "Vector4 copy constructor" << std::endl;
		}

//		Vector4(Vector4 &&other) noexcept:
//			_vectorImp(std::move(other._vectorImp)) {
//			std::cout << "Vector4 move constructor" << std::endl;
//		}

		~Vector4() {}

		//access operators
		float operator[](int i) const {
			assert(indexInRange(i));

			return _vectorImp.vec[i];
		}

		float& operator[](int i) { 
			assert(indexInRange(i));

			return _vectorImp.vec[i];
		}

		//assignment operator
		Vector4& operator=(const Vector4 &other) {
			_vectorImp = other._vectorImp;
			return *this;
		}

//		Vector4& operator=(Vector4 &&other) noexcept {
//			if (this != &other) {
//				_vectorImp = std::move(other._vectorImp);
//			}

//			return *this;
//		}

		//aritmetic operators
		Vector4& operator+=(const Vector4 &other) {
			_vectorImp.x += other._vectorImp.x;
			_vectorImp.y += other._vectorImp.y;
			_vectorImp.z += other._vectorImp.z;
			_vectorImp.w += other._vectorImp.w;

			return *this;
		}

		Vector4& operator-=(const Vector4 &other) {
			_vectorImp.x -= other._vectorImp.x;
			_vectorImp.y -= other._vectorImp.y;
			_vectorImp.z -= other._vectorImp.z;
			_vectorImp.w -= other._vectorImp.w;

			return *this;
		}

		Vector4 operator-() const {
			return (*this)*(-1);
		}

		Vector4& operator*=(ElementsType scalar) {
			_vectorImp.x *= scalar;
			_vectorImp.y *= scalar;
			_vectorImp.z *= scalar;
			_vectorImp.w *= scalar;

			return *this;
		}

		Vector4& operator/=(ElementsType scalar) {
			_vectorImp.x /= scalar;
			_vectorImp.y /= scalar;
			_vectorImp.z /= scalar;
			_vectorImp.w /= scalar;

			return *this;
		}

		friend Vector4 operator+(const Vector4 &left, const Vector4 &right);
		friend Vector4 operator-(const Vector4 &left, const Vector4 &right);
		friend Vector4 operator*(const Vector4 &vector, ElementsType scalar);
		friend Vector4 operator*(ElementsType scalar, const Vector4 &vector);
		friend Vector4 operator/(const Vector4 &vector, ElementsType scalar);

		friend Vector4 perElementProduct(const Vector4 &v1, const Vector4 &v2);

		//vector operations
		friend ElementsType dot(const Vector4 &left, const Vector4 &right);

		ElementsType norm() const {
			return sqrtf(dot(*this, *this));
		}

		Vector4& normalize() {
			return (*this) /= norm();
		}

		friend Vector4 normalized(const Vector4 &vector);

		bool isZero() const { return _vectorImp.x == 0.0f && _vectorImp.y == 0.0f && _vectorImp.z == 0.0f && _vectorImp.w == 0.0f; }

	private:
		//helper functions
		bool indexInRange(int index) const {
			return 0 <= index && index < 4;
		}

		union Vector4Imp{
			struct {
				ElementsType x;
				ElementsType y;
				ElementsType z;
				ElementsType w;
			};
			ElementsType vec[4];
		};

		Vector4Imp _vectorImp;
	};

	inline Vector4 operator+(const Vector4 &left, const Vector4 &right) {
		Vector4 aux(left);
		return aux += right;
	}

	inline Vector4 operator-(const Vector4 &left, const Vector4 &right) {
		Vector4 aux(left);
		return aux -= right;
	}

	inline Vector4 operator*(const Vector4 &vector, Vector4::ElementsType scalar) {
		Vector4 aux(vector);
		return aux *= scalar;
	}

	inline Vector4 operator*(Vector4::ElementsType scalar, const Vector4 &vector) {
		return vector*scalar;
	}
	
	inline Vector4 operator/(const Vector4 &vector, Vector4::ElementsType scalar) {
		Vector4 aux(vector);
		return aux /= scalar;
	}

	inline Vector4 perElementProduct(const Vector4 &v1, const Vector4 &v2) {
		return Vector4(v1._vectorImp.x * v2._vectorImp.x, v1._vectorImp.y * v2._vectorImp.y, v1._vectorImp.z * v2._vectorImp.z, v1._vectorImp.w * v2._vectorImp.w);
	}

	inline Vector4::ElementsType dot(const Vector4 &left, const Vector4 &right) {
		return left[0] * right[0] + left[1] * right[1] + left[2] * right[2] + left[3] * right[3];
	}

	inline Vector4 normalized(const Vector4 &vector) {
		Vector4 aux(vector);
		return aux.normalize();
	}
}

#endif // !_VECTOR4_H_
