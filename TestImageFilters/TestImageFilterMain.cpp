#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <Color.h>
#include <BoxFilter.h>
#include <Filter.h>
#include <GaussianFilter.h>
#include <Image.h>
#include <string>

K9::Image initImage(uchar *img, int cols, int rows);
uchar* imageToUchar(const K9::Image &img);
void saveImage(const K9::Image &img, const std::string &name);

K9::Image applyFilter(const K9::Image &img, K9::Filter *filter, float scale = 1.0f);

int main()
{
	using namespace cv;
	using namespace std;
	Mat image;
	image = imread("C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\TestImage.png", CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cout << image.channels() << endl;

	//to K9::Image
	K9::Image img = initImage(image.data, image.cols, image.rows);

	//apply filters
	K9::BoxFilter boxFilter(.5f);
	K9::Image boxFiltered = applyFilter(img, &boxFilter, 2.0f);
	saveImage(boxFiltered, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\BoxFiltered.png");

	K9::GaussianFilter gaussianFilter1;
	K9::Image gaussianFiltered1 = applyFilter(img, &gaussianFilter1, 1.0f);
	saveImage(gaussianFiltered1, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered1.png");

	K9::GaussianFilter gaussianFilter2(3.0f,6);
	K9::Image gaussianFiltered2 = applyFilter(img, &gaussianFilter2, 1.0f);
	saveImage(gaussianFiltered2, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered2.png");

	K9::GaussianFilter gaussianFilter3(1,2);
	K9::Image gaussianFiltered3 = applyFilter(img, &gaussianFilter3, 3.0f);
	saveImage(gaussianFiltered3, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered3.png");

	K9::GaussianFilter gaussianFilter4(1, 6);
	K9::Image gaussianFiltered4 = applyFilter(img, &gaussianFilter4, 1.0f);
	saveImage(gaussianFiltered4, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered4.png");

	//to Mat
	uchar* ucharImg = imageToUchar(boxFiltered);
	Mat out = Mat(boxFiltered.getHeight(), boxFiltered.getWidth(), CV_8UC3, (void *)ucharImg);

	namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
	imshow("Display window", out);                   // Show our image inside it.

	waitKey(0);                                          // Wait for a keystroke in the window

	//need to delete ucharImg?
	delete []ucharImg;
	return 0;
}

K9::Image initImage(uchar *img, int cols, int rows) {
	K9::Image out(cols, rows);
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < cols; c++) {
			K9::Color32 color = K9::setColor32(img[r*cols*3+c*3+2], img[r*cols*3 + c*3 + 1], img[r*cols*3 + c*3], 255);
			out.setColorAtXY(color, c, r);
		}
	}

	return out;
}

uchar* imageToUchar(const K9::Image &img) {
	uchar* out = new uchar[img.getWidth() * img.getHeight() * 3];

	for (int r = 0; r < img.getHeight(); ++r) {
		for (int c = 0; c < img.getWidth(); ++c) {
			K9::Color32 color = img.getColorAtXY(c, r);
			out[img.getWidth() * 3 * r + c * 3] = K9::getBlueColor32(color);
			out[img.getWidth() * 3 * r + c * 3 + 1] = K9::getGreenColor32(color);
			out[img.getWidth() * 3 * r + c * 3 + 2] = K9::getRedColor32(color);
		}
	}

	return out;
}

void saveImage(const K9::Image &img, const std::string &name) {
	using namespace cv;
	using namespace std;

	//to Mat
	uchar* ucharImg = imageToUchar(img);
	Mat out = Mat(img.getHeight(), img.getWidth(), CV_8UC3, (void *)ucharImg);

	imwrite(name.c_str(), out);   // write to file

	delete[]ucharImg;
}

K9::Image applyFilter(const K9::Image &img, K9::Filter *filter, float scale /*=1.0f*/) {
	unsigned int nx = img.getWidth();
	unsigned int ny = img.getHeight();
	K9::Image out(nx, ny);

	float r = filter->getRadius()*scale;

	//TODO: use a unique pointer of float[] instead.
	float *SR = new float[nx];
	float *SG = new float[nx];
	float *SB = new float[nx];

	for (int j = 0; j < ny; ++j) {
		for (int k = 0; k < nx; ++k) {
			SR[k] = 0.0f;
			SG[k] = 0.0f;
			SB[k] = 0.0f;
			float filterValueSumCol = 0.0f;
			float minJp = std::max(static_cast<int>(ceilf(j - r)), 0);
			float maxJp = std::min(static_cast<unsigned int>(j + r), ny-1);
			for (int jp = minJp; jp <= maxJp; ++jp) {
				K9::Color32 color = img.getColorAtXY(k, jp);
				float filterValue = filter->executeScaled(j - jp, scale);
				filterValueSumCol += filterValue;
				SR[k] += static_cast<float>(K9::getRedColor32(color))*filterValue;
				SG[k] += static_cast<float>(K9::getGreenColor32(color))*filterValue;
				SB[k] += static_cast<float>(K9::getBlueColor32(color))*filterValue;
			}
			SR[k] /= filterValueSumCol;
			SG[k] /= filterValueSumCol;
			SB[k] /= filterValueSumCol;
		}

		for (int i = 0; i < nx; ++i) {
			float filterValueSumRow = 0.0f;
			float minIp = std::max(static_cast<int>(ceilf(i - r)), 0);
			float maxIp = std::min(static_cast<unsigned int>(i + r), nx - 1);
			float red = 0;
			float green = 0;
			float blue = 0;
			
			for (int ip = minIp; ip <= maxIp; ++ip) {
				float filterValue = filter->executeScaled(i - ip, scale);
				filterValueSumRow += filterValue;
				
				red +=  SR[ip] * filterValue;
				green += SG[ip] * filterValue;
				blue += SB[ip] * filterValue;				
			}

			float filterValueSum = filterValueSumRow;
			red = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(red / filterValueSum))));
			green = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(green / filterValueSum))));
			blue = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(blue / filterValueSum))));

			K9::Color32 color = K9::setColor32(red, green, blue, 255);
			out.setColorAtXY(color, i, j);
		}
	}

	delete[]SB;
	delete[]SG;
	delete[]SR;

	return out;
}