#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include <string>
#include <Vector4.h>

namespace K9 {
	class Matrix4 {
		typedef float ElementsType;
	public:
		Matrix4():
			Matrix4(0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0){
		}

		Matrix4(ElementsType m00, ElementsType m01, ElementsType m02, ElementsType m03,
				ElementsType m10, ElementsType m11, ElementsType m12, ElementsType m13,
				ElementsType m20, ElementsType m21, ElementsType m22, ElementsType m23,
				ElementsType m30, ElementsType m31, ElementsType m32, ElementsType m33) {
			_matrix.m00 = m00;
			_matrix.m01 = m01;
			_matrix.m02 = m02;
			_matrix.m03 = m03;
			_matrix.m10 = m10;
			_matrix.m11 = m11;
			_matrix.m12 = m12;
			_matrix.m13 = m13;
			_matrix.m20 = m20;
			_matrix.m21 = m21;
			_matrix.m22 = m22;
			_matrix.m23 = m23;
			_matrix.m30 = m30;
			_matrix.m31 = m31;
			_matrix.m32 = m32;
			_matrix.m33 = m33;
		}

		~Matrix4() = default;

		Matrix4(const Matrix4 &other) {
			std::memcpy((void*)_matrix.elements, (void*)other._matrix.elements, sizeof(ElementsType) * 16);
		}

//		Matrix4(Matrix4 &&other) noexcept:
//			_matrix(std::move(other._matrix)){
//		}

		Matrix4& operator=(const Matrix4 &other) {
			std::memcpy((void*)_matrix.elements, (void*)other._matrix.elements, sizeof(ElementsType) * 16);
			return *this;
		}

//		Matrix4& operator=(Matrix4 &&other) noexcept {
//			if (this != &other) {
//				_matrix = std::move(other._matrix);
//			}
//			return *this;
//		}

		Matrix4& operator+=(const Matrix4 &other) {
			_matrix.m00 += other._matrix.m00;
			_matrix.m01 += other._matrix.m01;
			_matrix.m02 += other._matrix.m02;
			_matrix.m03 += other._matrix.m03;

			_matrix.m10 += other._matrix.m10;
			_matrix.m11 += other._matrix.m11;
			_matrix.m12 += other._matrix.m12;
			_matrix.m13 += other._matrix.m13;

			_matrix.m20 += other._matrix.m20;
			_matrix.m21 += other._matrix.m21;
			_matrix.m22 += other._matrix.m22;
			_matrix.m23 += other._matrix.m23;

			_matrix.m30 += other._matrix.m30;
			_matrix.m31 += other._matrix.m31;
			_matrix.m32 += other._matrix.m32;
			_matrix.m33 += other._matrix.m33;

			return *this;
		}

		Matrix4 operator-() const{
			return (*this)*(-1);
		}

		Matrix4& operator-=(const Matrix4 &other) {
			return (*this)+=(-other);
		}

		Matrix4& operator*=(const Matrix4 &other) {
			for (int i = 0; i < 4; ++i) {
				ElementsType aux0 = _matrix.elementsMat[i][0];
				ElementsType aux1 = _matrix.elementsMat[i][1];
				ElementsType aux2 = _matrix.elementsMat[i][2];
				ElementsType aux3 = _matrix.elementsMat[i][3];

				_matrix.elementsMat[i][0] = aux0*other._matrix.m00 +
					aux1*other._matrix.m10 +
					aux2*other._matrix.m20 +
					aux3*other._matrix.m30;

				_matrix.elementsMat[i][1] = aux0*other._matrix.m01 +
					aux1*other._matrix.m11 +
					aux2*other._matrix.m21 +
					aux3*other._matrix.m31;

				_matrix.elementsMat[i][2] = aux0*other._matrix.m02 +
					aux1*other._matrix.m12 +
					aux2*other._matrix.m22 +
					aux3*other._matrix.m32;

				_matrix.elementsMat[i][3] = aux0*other._matrix.m03 +
					aux1*other._matrix.m13 +
					aux2*other._matrix.m23 +
					aux3*other._matrix.m33;
			}

			return *this;
		}

		Matrix4& operator*=(ElementsType scalar) {
			_matrix.m00 *= scalar;
			_matrix.m01 *= scalar;
			_matrix.m02 *= scalar;
			_matrix.m03 *= scalar;

			_matrix.m10 *= scalar;
			_matrix.m11 *= scalar;
			_matrix.m12 *= scalar;
			_matrix.m13 *= scalar;

			_matrix.m20 *= scalar;
			_matrix.m21 *= scalar;
			_matrix.m22 *= scalar;
			_matrix.m23 *= scalar;

			_matrix.m30 *= scalar;
			_matrix.m31 *= scalar;
			_matrix.m32 *= scalar;
			_matrix.m33 *= scalar;

			return *this;
		}

		Matrix4& operator/=(ElementsType scalar) {
			return (*this) *= (1.0f / scalar);
		}

		friend Matrix4 operator+(const Matrix4 &m1, const Matrix4 &m2);
		friend Matrix4 operator-(const Matrix4 &m1, const Matrix4 &m2);
		friend Matrix4 operator*(const Matrix4 &m1, const Matrix4 &m2);
		friend Vector4 operator*(const Matrix4 &m, const Vector4 &vector);
		friend Matrix4 operator*(const Matrix4 &m, ElementsType scalar);
		friend Matrix4 operator/(const Matrix4 &m, ElementsType scalar);
		friend Matrix4 operator*(ElementsType scalar, const Matrix4 &m);

	private:
		union Matrix4Imp{
			struct {
				ElementsType m00;
				ElementsType m01;
				ElementsType m02;
				ElementsType m03;
				ElementsType m10;
				ElementsType m11;
				ElementsType m12;
				ElementsType m13;
				ElementsType m20;
				ElementsType m21;
				ElementsType m22;
				ElementsType m23;
				ElementsType m30;
				ElementsType m31;
				ElementsType m32;
				ElementsType m33;
			};

			ElementsType elements[16];
			ElementsType elementsMat[4][4];
		};

		Matrix4Imp _matrix;
	};

	inline Matrix4 operator+(const Matrix4 &m1, const Matrix4 &m2) {
		Matrix4 ret(m1);
		return ret += m2;
	}

	inline Matrix4 operator-(const Matrix4 &m1, const Matrix4 &m2) {
		Matrix4 ret(m1);
		return ret -= m2;
	}

	inline Matrix4 operator*(const Matrix4 &m1, const Matrix4 &m2) {
		Matrix4 ret(m1);
		return ret *= m2;
	}

	inline Vector4 operator*(const Matrix4 &m, const Vector4 &vector) {
		Vector4 r0(m._matrix.m00, m._matrix.m01, m._matrix.m02, m._matrix.m03);
		Vector4 r1(m._matrix.m10, m._matrix.m11, m._matrix.m12, m._matrix.m13);
		Vector4 r2(m._matrix.m20, m._matrix.m21, m._matrix.m22, m._matrix.m23);
		Vector4 r3(m._matrix.m30, m._matrix.m31, m._matrix.m32, m._matrix.m33);
		return Vector4(dot(r0, vector), dot(r1, vector), dot(r2, vector), dot(r3, vector));
	}

	inline Matrix4 operator*(const Matrix4 &m, Matrix4::ElementsType scalar) {
		Matrix4 ret(m);
		return ret *= scalar;
	}

	inline Matrix4 operator/(const Matrix4 &m, Matrix4::ElementsType scalar) {
		Matrix4 ret(m);
		return ret /= scalar;
	}

	inline Matrix4 operator*(Matrix4::ElementsType scalar, const Matrix4 &m) {
		Matrix4 ret(m);
		return ret *= scalar;
	}
}

#endif // !_MATRIX4_H_
