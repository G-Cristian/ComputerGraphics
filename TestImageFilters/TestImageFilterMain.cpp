#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <Color.h>
#include <BoxFilter.h>
#include <Filter.h>
#include <GaussianFilter.h>
#include <Image.h>
#include <ImageOperations.h>
#include <SharpFilter.h>
#include <string>

K9::Image initImage(uchar *img, int cols, int rows);
uchar* imageToUchar(const K9::Image &img);
void saveImage(const K9::Image &img, const std::string &name);

int main()
{
	using namespace cv;
	using namespace std;
	Mat image;
	Mat imageCircles;
	image = imread("C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\TestImage.png", CV_LOAD_IMAGE_COLOR);   // Read the file
	imageCircles = imread("C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\scaledDown_3_3_GussianFilter1.png", CV_LOAD_IMAGE_COLOR);   // Read the file

	if (!image.data || !imageCircles.data)                              // Check for invalid input
	{
		cout << "Could not open or find the image" << std::endl;
		return -1;
	}

	cout << image.channels() << endl;

	::K9::Images::ImageOperations imageOperations;
	//to K9::Image
	K9::Image img = initImage(image.data, image.cols, image.rows);
	K9::Image imgCircles = initImage(imageCircles.data, imageCircles.cols, imageCircles.rows);

	////apply filters
	//K9::BoxFilter boxFilter(.5f);
	//K9::Image boxFiltered = imageOperations.applyFilter(img, &boxFilter, 2.0f);
	//saveImage(boxFiltered, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\BoxFiltered.png");

	//K9::GaussianFilter gaussianFilter1;
	//K9::Image gaussianFiltered1 = imageOperations.applyFilter(img, &gaussianFilter1, 1.0f);
	//saveImage(gaussianFiltered1, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered1.png");

	//K9::GaussianFilter gaussianFilter2(3.0f,6);
	//K9::Image gaussianFiltered2 = imageOperations.applyFilter(img, &gaussianFilter2, 1.0f);
	//saveImage(gaussianFiltered2, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered2.png");

	//K9::GaussianFilter gaussianFilter3(1,2);
	//K9::Image gaussianFiltered3 = imageOperations.applyFilter(img, &gaussianFilter3, 3.0f);
	//saveImage(gaussianFiltered3, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered3.png");

	//K9::GaussianFilter gaussianFilter4(1, 6);
	//K9::Image gaussianFiltered4 = imageOperations.applyFilter(img, &gaussianFilter4, 1.0f);
	//saveImage(gaussianFiltered4, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\GaussianFiltered4.png");

	//K9::SharpFilter sharpFilter1(0.5f);
	//K9::Image sharpFiltered1 = imageOperations.applyFilter(img, &sharpFilter1, 1.0f);
	//saveImage(sharpFiltered1, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\sharpFiltered1.png");

	//K9::SharpFilter sharpFilterCircles1(1.0f);
	//K9::Image sharpFilteredCircles1 = imageOperations.applyFilter(imgCircles, &sharpFilterCircles1, 1.0f);
	//saveImage(sharpFilteredCircles1, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\sharpFilteredCircles1.png");

	K9::GaussianFilter scaleUp_3_3_GussianFilter1(1.0f, 1.0f);
	K9::Image scaledUp_3_3_GussianFilter1 = imageOperations.resample(imgCircles, imgCircles.getWidth() * 3, imgCircles.getHeight() * 3, scaleUp_3_3_GussianFilter1);
	saveImage(scaledUp_3_3_GussianFilter1, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\scaledDownUp_3_3_GussianFilter1.png");

	//K9::GaussianFilter scaleDown_3_3_GussianFilter1(1.0f, 3.0f);
	//K9::Image scaledDown_3_3_GussianFilter1 = imageOperations.resample(imgCircles, imgCircles.getWidth() / 3.0f , imgCircles.getHeight() / 3.0f, scaleDown_3_3_GussianFilter1);
	//saveImage(scaledDown_3_3_GussianFilter1, "C:\\Users\\Cristian\\Documents\\GitHub\\ComputerGraphics\\TestImageFilters\\scaledUpDown_3_3_GussianFilter1.png");

	//to Mat
	uchar* ucharImg = imageToUchar(scaledUp_3_3_GussianFilter1);
	Mat out = Mat(scaledUp_3_3_GussianFilter1.getHeight(), scaledUp_3_3_GussianFilter1.getWidth(), CV_8UC3, (void *)ucharImg);

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