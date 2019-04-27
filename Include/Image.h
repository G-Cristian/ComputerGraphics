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

		class IIterator {
		public:
			IIterator(ElementsType *pos) :_pos(pos) {
			}
			virtual ~IIterator() = default;
			
			bool operator==(const IIterator& r) const{
				return this->_pos == r._pos;
			}

			bool operator!=(const IIterator& r) const {
				return !(*this == r);
			}

			virtual IIterator& operator++() = 0;
			virtual const ElementsType at(size_t i) const = 0;
			virtual ElementsType& at(size_t i) = 0;
		protected:
			ElementsType *_pos;
		};

		class RowIterator:public IIterator {
		public:
			RowIterator(ElementsType *pos, size_t imageWidth):
				IIterator(pos),
				_width(imageWidth){
			}
			virtual ~RowIterator() = default;

			RowIterator& operator++() override final {
				_pos += _width;
				return *this;
			}

			const ElementsType at(size_t i) const override final {
				return *(_pos + i);
			}
			ElementsType& at(size_t i) override final {
				return *(_pos + i);
			}
		private:
			size_t _width;
		};

		class ColumnIterator :public IIterator {
		public:
			ColumnIterator(ElementsType *pos, size_t imageWidth) :
				IIterator(pos),
				_width(imageWidth) {
			}
			virtual ~ColumnIterator() = default;

			ColumnIterator& operator++() override final {
				++_pos;
				return *this;
			}

			const ElementsType at(size_t i) const override final {
				return *(_pos + _width*i);
			}
			ElementsType& at(size_t i) override final {
				return *(_pos + _width*i);
			}
		private:
			size_t _width;
		};

		RowIterator rowInter(size_t rowI) const{
			return RowIterator(_image + _width*rowI, _width);
		}

		RowIterator rowInter(size_t rowI) {
			return RowIterator(_image + _width*rowI, _width);
		}

		ColumnIterator columnI(size_t columnI) const{
			return ColumnIterator(_image + columnI, _width);
		}

		ColumnIterator columnI(size_t columnI) {
			return ColumnIterator(_image + columnI, _width);
		}

	private:
		//copy helpers
		ElementsType *copyImage(const ElementsType *image, size_t size) const;

		ElementsType *_image;
		unsigned int _width;
		unsigned int _height;
	};
}

#endif // !_IMAGE_H_
