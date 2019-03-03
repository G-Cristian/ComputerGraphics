#ifndef _IMAGE_H_
#define _IMAGE_H_

//My libraries
#include <Color.h>
//Other libraries
#include <memory>
#include <vector>

namespace K9 {
	class Image {
	public:
		typedef Color32 ElementsType;
		//constructors
		explicit Image(unsigned int width, unsigned int height);
		//copy constructor
		Image(const Image &other);
		//move constructor
		Image(Image &&other) noexcept;
		//destructor
		~Image();
		//assignment operator
		Image& operator=(const Image &other);
		//move assignment operator
		Image& operator=(Image &&other) noexcept;
		//cast operators
		explicit operator unsigned char*() const;
		//setters
		void setColorAtXY(ElementsType color, unsigned int x, unsigned int y) {
			//TODO: check x & y in range
			_image[y*_width + x] = color;
		}

		//getters
		const ElementsType &getColorAtXY(unsigned int x, unsigned int y) const {
			//TODO: check x & y in range
			return _image[y*_width + x];
		}

		ElementsType &getColorAtXY(unsigned int x, unsigned int y) {
			//TODO: check x & y in range
			return _image[y*_width + x];
		}

		unsigned int getWidth() const { return _width; }
		unsigned int getHeight() const { return _height; }

	private:
		//copy helpers
		ElementsType *copyImage(const ElementsType *image, size_t size) const;

		ElementsType *_image;
		unsigned int _width;
		unsigned int _height;
	};
}

#endif // !_IMAGE_H_
