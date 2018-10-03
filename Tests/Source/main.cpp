#include <iostream>
#include <Vector3.h>

using namespace std;

int main() {
	using namespace K9;

	Vector3 v1(2, 3, 4);
	Vector3 v2(5, 6, 7);

	float x1 = v1[0];
	float y1 = v1[1];
	float z1 = v1[2];

	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << endl;

	float x2 = v2[0];
	float y2 = v2[1];
	float z2 = v2[2];

	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << endl;

	Vector3 sum = v1 - v2;
	cout << "sum[0]: " << sum[0] << " sum[1]: " << sum[1] << " sum[2]: " << sum[2] << endl;

	float norm1 = v1.norm();
	cout << "norm1: " << norm1 << endl;

	Vector3 v1Normalized(v1);
	v1Normalized.normalize();

	cout << "v1Normalized[0]: " << v1Normalized[0] << " v1Normalized[1]: " << v1Normalized[1] << " v1Normalized[2]: " << v1Normalized[2] << endl;

	Vector3 v3(v2);
	float x3 = v3[0];
	float y3 = v3[1];
	float z3 = v3[2];
	cout << "x3: " << x3 << " y3: " << y3 << " z3: " << z3 << endl;

	v2[0] = 7;
	x2 = v2[0];
	v3[1] = 8;
	y3 = v3[1];
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << endl;
	cout << "x3: " << x3 << " y3: " << y3 << " z3: " << z3 << endl;

	swap(v1, v2);

	x1 = v1[0];
	y1 = v1[1];
	z1 = v1[2];

	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << endl;

	x2 = v2[0];
	y2 = v2[1];
	z2 = v2[2];

	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << endl;

	v2[2] = 10;
	x2 = v2[2];
	v1[1] = 20;
	y1 = v1[1];

	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << endl;
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << endl;

	return 0;
}