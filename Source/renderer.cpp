#include "../Include/renderer.h"
#include <algorithm>
#include <iostream>

using namespace std;
namespace K9 {

	Renderer::Renderer(Window &window) {
		_window = Window();
		_window.name = window.name;
		_window.width = window.width;
		_window.height = window.height;

		_img = Mat(window.height, window.width, CV_8UC3, Scalar(255, 255, 255));
	}

	Renderer::~Renderer() {

	}

	void Renderer::resizeWindow(int width, int height) {
		_window.width = width;
		_window.height = height;

		resize(_img, _img, Size(width, height));
	}

	void Renderer::drawPoint(const Geometry::Point2D &coord, const Color &color) {
		_img.at<cv::Vec3b>(cv::Point(coord.x, coord.y)) = cv::Vec3b(static_cast<uchar>(color[0]* 255), static_cast<uchar>(color[1] * 255), static_cast<uchar>(color[2] * 255));
	}

	void Renderer::show(int x, int y)  const {
		imshow(_window.name, _img);
		moveWindow(_window.name, x, y);
	}

	void Renderer::exportToImage(std::string imageName) const {
		imwrite(imageName, _img);
	}

}