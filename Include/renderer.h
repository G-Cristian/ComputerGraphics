#ifndef _RENDERER_H_
#define _RENDERER_H_

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <vector>
#include <string>

#include "Point2D.h"

#include <Vector3.h>
#include <Vector4.h>

using namespace std;
using namespace cv;

namespace K9 {
	typedef Vector4 Color;

	class Renderer {
	public:
		struct Window {
			cv::String name;
			int width;
			int height;
		};

		Renderer(Window &window);
		~Renderer();

		const Window& window() const { return _window; }

		void resizeWindow(int width, int height);

		void drawPoint(const ::Geometry::Point2D &coord, const Color &color);

		void show(int x, int y) const;
		void exportToImage(std::string imageName) const;

	private:
		Window _window;
		cv::Mat _img;
	};

}

#endif
