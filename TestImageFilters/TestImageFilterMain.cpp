#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include <Color.h>
#include <BoxFilter.h>
#include <Filter.h>
#include <Image.h>

K9::Image initImage(uchar *img, int cols, int rows);
uchar* imageToUchar(const K9::Image &img);

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
	K9::BoxFilter boxFilter;
	K9::Image boxFiltered = applyFilter(img, &boxFilter, 2.0f);

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

K9::Image applyFilter(const K9::Image &img, K9::Filter *filter, float scale /*=1.0f*/) {
	unsigned int nx = img.getWidth();
	unsigned int ny = img.getHeight();
	K9::Image out(nx, ny);

	float r = filter->getRadius();

	//TODO: use a unique pointer of float[] instead.
	float *SR = new float[nx];
	float *SG = new float[nx];
	float *SB = new float[nx];

	for (int j = static_cast<int>(ceilf(r)); j < static_cast<int>(ny - r); ++j) {
		for (int k = 0; k < nx; ++k) {
			SR[k] = 0.0f;
			SG[k] = 0.0f;
			SB[k] = 0.0f;
			for (int jp = static_cast<int>(ceilf(j - r)); jp <= static_cast<int>(j + r); ++jp) {
				K9::Color32 color = img.getColorAtXY(k, jp);
				float filterValue = filter->executeScaled(j - jp, scale);
				SR[k] += K9::getRedColor32(color)*filterValue;
				SG[k] += K9::getGreenColor32(color)*filterValue;
				SB[k] += K9::getBlueColor32(color)*filterValue;
			}
		}

		for (int i = static_cast<int>(ceilf(r)); i < static_cast<int>(nx - r);++i) {
			for (int ip = static_cast<int>(ceilf(i - r)); ip <= static_cast<int>(i + r); ++ip) {
				float filterValue = filter->executeScaled(i - ip, scale);
				K9::Color32 color = K9::setColor32(SR[ip] * filterValue, SG[ip] * filterValue, SB[ip] * filterValue, 255);
				out.setColorAtXY(color, i, j);
			}
		}
	}

	delete[]SB;
	delete[]SG;
	delete[]SR;

	return out;
}