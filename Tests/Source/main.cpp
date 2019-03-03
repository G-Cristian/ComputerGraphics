#include <iostream>
#include <Vector3.h>
#include <Vector4.h>
#include <Color.h>
#include <Image.h>

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
	z2 = v2[2];
	v1[1] = 20;
	y1 = v1[1];

	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << endl;
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << endl;

	cout << "VECTOR4 TESTS" << endl;

	Vector4 v41(2, 3, 4, 1);
	float *v4vec = new float[4]();
	v4vec[0] = 5;
	v4vec[1] = 6;
	v4vec[2] = 7;
	v4vec[3] = 0;
	Vector4 v42(v4vec);

	x1 = v41[0];
	y1 = v41[1];
	z1 = v41[2];
	float w1 = v41[3];

	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << " w1: " << w1 << endl;

	v4vec[0] = 9;
	v4vec[1] = 9;
	v4vec[2] = 9;
	v4vec[3] = 9;

	x2 = v42[0];
	y2 = v42[1];
	z2 = v42[2];
	float w2 = v42[3];

	cout << "v4vec[0]: " << v4vec[0] << " v4vec[1]: " << v4vec[1] << " v4vec[2]: " << v4vec[2] << " v4vec[3]: " << v4vec[3] << endl;
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << " w2: " << w2 << endl;

	
	Vector4 sum4 = v41 - v42;
	cout << "sum4[0]: " << sum4[0] << " sum4[1]: " << sum4[1] << " sum4[2]: " << sum4[2] << " sum4[3]: " << sum4[3] << endl;

	float norm41 = v41.norm();
	cout << "norm41: " << norm41 << endl;

	Vector4 v41Normalized(v41);
	v41Normalized.normalize();

	cout << "v41Normalized[0]: " << v41Normalized[0] << " v41Normalized[1]: " << v41Normalized[1] << " v41Normalized[2]: " << v41Normalized[2] << " v41Normalized[3]: " << v41Normalized[3] << endl;
	

	Vector4 v43(v42);
	x3 = v43[0];
	y3 = v43[1];
	z3 = v43[2];
	float w3 = v43[3];
	cout << "x3: " << x3 << " y3: " << y3 << " z3: " << z3 << " w3: " << w3 << endl;
	
	v42[0] = 7;
	x2 = v42[0];
	v43[1] = 8;
	y3 = v43[1];
	cout << "v4vec[0]: " << v4vec[0] << " v4vec[1]: " << v4vec[1] << " v4vec[2]: " << v4vec[2] << " v4vec[3]: " << v4vec[3] << endl;
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << " w2: " << w2 << endl;
	cout << "x3: " << x3 << " y3: " << y3 << " z3: " << z3 << " w3: " << w3 << endl;

	//swap(v1, v2);

	x1 = v41[0];
	y1 = v41[1];
	z1 = v41[2];

	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << " w1: " << w1 << endl;

	x2 = v42[0];
	y2 = v42[1];
	z2 = v42[2];

	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << " w2: " << w2 << endl;

	delete[] v4vec;

	v42[3] = 10;
	w2 = v42[3];
	v41[1] = 20;
	y1 = v41[1];

	//cout << "v4vec[0]: " << v4vec[0] << " v4vec[1]: " << v4vec[1] << " v4vec[2]: " << v4vec[2] << " v4vec[3]: " << v4vec[3] << endl;
	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << " w1: " << w1 << endl;
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << " w2: " << w2 << endl;

	Vector4 v44 = v41 + v42;
	cout << "x1: " << x1 << " y1: " << y1 << " z1: " << z1 << " w1: " << w1 << endl;
	cout << "x2: " << x2 << " y2: " << y2 << " z2: " << z2 << " w2: " << w2 << endl;
	cout << "x4: " << v44[0] << " y4: " << v44[1] << " z4: " << v44[2] << " w4: " << v44[3] << endl;

	cout << "COLOR" << endl;

	Color32 color = setColor32(100, 200, 0, 255);

	cout << "red: " << (Color32)getRedColor32(color) << " green: " << (Color32)getGreenColor32(color) << " blue: " << (Color32)getBlueColor32(color) << " alpha: " << (Color32)getAlphaColor32(color) << endl;

	cout << "IMAGE" << endl;

	Image image(2, 2);
	image.setColorAtXY(color, 0, 1);
	image.setColorAtXY(setColor32(0,0,255,255), 1, 0);

	for (int y = 0; y < 2; ++y) {
		for (int x = 0; x < 2; ++x) {
			cout << "red: " << (Color32)getRedColor32(image.getColorAtXY(x,y)) << " green: " << (Color32)getGreenColor32(image.getColorAtXY(x, y)) << " blue: " << (Color32)getBlueColor32(image.getColorAtXY(x, y)) << " alpha: " << (Color32)getAlphaColor32(image.getColorAtXY(x, y)) << endl;
		}
	}

	cout << endl;

	unsigned char *copy = (unsigned char *)(image);
	unsigned char *copyAux = copy;

	for (int x = 0; x < 2; x++) {
		for (int y = 0; y < 2; y++) {
			cout << "red: " << (Color32)*(copyAux++);
			cout << " green: " << (Color32)*(copyAux++);
			cout << " blue: " << (Color32)*(copyAux++); 
			cout << " alpha: " << (Color32)*(copyAux++) << endl;
		}
	}

	delete[]copy;

	return 0;
}