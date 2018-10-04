#ifndef _MATHUTILITY_H_
#define _MATHUTILITY_H_

#include <math.h>
#include <memory>

#define E_1_100000 0.00001f

#define FLOAT_EQ(f1, f2, epsilon) (abs(f1 - f2) <= epsilon)

namespace K9 {

	class MathUtility {
	public:
		static char solveQuadraticEquation(float a, float b, float c, float &outX1, float &outX2);
	};

}

#endif // !_MATHUTILITY_H_
