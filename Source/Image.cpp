//My libraries
#include <Color.h>
#include <Image.h>
//Other libraries
#include <memory>
#include <vector>

namespace K9 {
	Image::Image(unsigned int width, unsigned int height) :
		_width(width)
		, _height(height) {
		_image = new ElementsType[_width*_height]();
	}

	Image::Image(const Image &other) :
		  _width(other._width)
		, _height(other._height){
		_image = copyImage(other._image, _width * _height);
	}

	Image::Image(Image &&other) noexcept :
		  _width(other._width)
		, _height(other._height)
		, _image(other._image) {
		other._image = nullptr;
	}

	Image::~Image() {
		delete[] _image;
		_image = nullptr;
	}

	Image& Image::operator=(const Image &other) {
		ElementsType *auxImage = copyImage(other._image, other._width * other._height);
		delete[] _image;
		_image = auxImage;
		_width = other._width;
		_height = other._height;

		return *this;
	}

	Image& Image::operator=(Image &&other) noexcept {
		if (this != &other) {
			_image = other._image;
			other._image = nullptr;
			_width = other._width;
			_height = other._height;
		}

		return *this;
	}

	Image::operator unsigned char*() const {
		size_t size = _width * _height * sizeof(ElementsType);
		unsigned char *other = new unsigned char[size];
		//TODO: make sure that 'memcpy' works since 'other' was created with 'new'
		memcpy((void*)(other), (void*)(_image), size);

		return other;
	}

	Image::ElementsType *Image::copyImage(const ElementsType *image, size_t size) const {
		ElementsType *other = new ElementsType[size];
		//TODO: maybe replace for memcpy
		for (size_t i = 0; i < size; ++i) {
			other[i] = image[i];
		}

		return other;
	}
}