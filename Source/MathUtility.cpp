#include <MathUtility.h>

namespace K9 {
	///solves a quadratic equation
	///@param a: first tetm of quadratic
	///@param b: second tetm of quadratic
	///@param c: third tetm of quadratic
	///@param outX1: first root if any
	///@param outX12: second root if any
	///returns the number of roots (0, 1 or 2)
	char MathUtility::solveQuadraticEquation(float a, float b, float c, float &outX1, float &outX2) {
		outX1 = outX2 = 0.0f;
		char numberOfSolutions = 0;
		float discriminant = b*b - 4 * a*c;
		
		if (discriminant >= 0) {
			numberOfSolutions = (FLOAT_EQ(discriminant, 0.0f, E_1_100000) ? 1 : 2);
			float scrtDiscriminant = sqrtf(discriminant);
			if (b < 0) {
				float aux = -b + scrtDiscriminant;
				outX1 = aux / (2 * a);
				outX2 = (2 * c) / aux;
			}
			else {
				float aux = -b - scrtDiscriminant;
				outX1 = (2 * c) / aux;
				outX2 = aux / (2 * a);
			}
		}

		return numberOfSolutions;
	}

}