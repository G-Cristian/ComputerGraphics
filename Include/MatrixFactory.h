#ifndef _MATRIXFACTORY_H_
#define _MATRIXFACTORY_H_

#define _USE_MATH_DEFINES

#include <math.h>
#include <Matrix4.h>
#include <Vector3.h>

namespace K9 {
	class MatrixFactory {
	public:
		static Matrix4 scale(float sx, float sy, float sz) {
			return Matrix4(	sx,		0.0f,	0.0f,	0.0f,
							0.0f,	sy,		0.0f,	0.0f,
							0.0f,	0.0f,	sz,		0.0f,
							0.0f,	0.0f,	0.0f,	1.0f);
		}

		static Matrix4 move(float x, float y, float z) {
			return Matrix4(1.0f, 0.0f, 0.0f, x,
				0.0f, 1.0f, 0.0f, y,
				0.0f, 0.0f, 1.0f, z,
				0.0f, 0.0f, 0.0f, 1.0f);
		}

		static Matrix4 rotateX(float angle) {
			return Matrix4(	1.0f,	0.0f,			0.0f,			0.0f,
							0.0f,	cosf(angle),	-sinf(angle),	0.0f,
							0.0f,	sinf(angle),	cosf(angle),	0.0f,
							0.0f,	0.0f,			0.0f,			1.0f);
		}

		static Matrix4 rotateY(float angle) {
			return Matrix4(	cosf(angle),	0.0f,	sinf(angle),	0.0f,
							0.0f,			1.0f,	0.0f,			0.0f,
							-sinf(angle),	0.0f,	cosf(angle),	0.0f,
							0.0f,			0.0f,	0.0f,			1.0f);
		}

		static Matrix4 rotateZ(float angle) {
			return Matrix4(	cosf(angle),	-sinf(angle),	0.0f, 0.0f,
							sinf(angle),	cosf(angle),	0.0f, 0.0f,
							0.0f,			0.0f,			1.0f, 0.0f,
							0.0f,			0.0f,			0.0f, 1.0f);
		}

		static Matrix4 viewportTransformation(float nx, float ny) {
			return Matrix4(	nx/2.0f,	0.0f,		0.0f,	(nx-1)/2.0f,
							0.0f,		ny / 2.0f,	0.0f,	(ny - 1) / 2.0f,
							0.0f,		0.0f,		1.0f,	0.0f,
							0.0f,		0.0f,		0.0f,	1.0f);
		}

		static Matrix4 perspectiveTransformation(float l, float b, float n, float r, float t, float f) {
			return Matrix4(	(2.0f*n) / (r - l),	0.0f,				(l + r) / (l - r),	0.0f,
							0.0f,				(2.0f*n) / (t - b), (b + t) / (b - t),	0.0f,
							0.0f,				0.0f,				(f + n) / (n - f),	(2.0f*f*n) / (f - n),
							0.0f,				0.0f,				1.0f,				0.0f);
		}

		static Matrix4 cameraTransformation(Vector3 u, Vector3 v, Vector3 w, Vector3 pos) {
			return Matrix4(	u[0], u[1], u[2], 0.0f,
							v[0], v[1], v[2], 0.0f,
							w[0], w[1], w[2], 0.0f,
							0.0f, 0.0f, 0.0f, 1.0f ) *
				   Matrix4(1.0f, 0.0f, 0.0f, -pos[0],
					   0.0f, 1.0f, 0.0f, -pos[1],
					   0.0f, 0.0f, 1.0f, -pos[2],
					0.0f, 0.0f, 0.0f, 1.0f);
		}
	private:
		MatrixFactory() = delete;
		~MatrixFactory() = delete;
	};
}

#endif // !_MATRIXFACTORY_H_
