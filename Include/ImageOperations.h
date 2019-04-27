#ifndef _IMAGEOPERATIONS_H_
#define _IMAGEOPERATIONS_H_

#include <Filter.h>
#include <Image.h>

namespace K9 {
	namespace Images {
		class ImageOperations {
		public:
			ImageOperations() = default;
			~ImageOperations() = default;

			::K9::Image applyFilter(const ::K9::Image &img, ::K9::Filter *filter, float scale = 1.0f);
			::K9::Image resample(const ::K9::Image &imageIn, float newWidth, float newHeight, const ::K9::Filter &filter)const;
			::K9::Image resample(const ::K9::Image &imageIn, float xl, float xh, float yl, float yh, float newWidth, float newHeight, const ::K9::Filter &filter)const;
		private:
			::K9::Image resampleRows(const ::K9::Image &imageIn, float xl, float xh, float yl, float yh, float newWidth, float newHeight, const ::K9::Filter &filter)const;
			::K9::Image resampleColumns(const ::K9::Image &imageIn, float xl, float xh, float yl, float yh, float newWidth, float newHeight, const ::K9::Filter &filter)const;
			//TODO:	Implement Abstract, Rows and Columns Iterators in Image
			//		Replace these two methods for one method that receives an Abstract Iterator for the imageIn and ImageOut.
			void resampleSec(::K9::Image::IIterator &itIn, int size, float l, float h, int newLenght, const ::K9::Filter &filter, ::K9::Image::IIterator &itOut)const;
			/*void resampleRowI(const Image::IIterator &itIn, float l, float h, float newLenght, const ::K9::Filter &filter, ::K9::Image &imageOut)const;
			void resampleColumnI(const ::K9::Image &imageIn, int columnI, float l, float h, float newLenght, const ::K9::Filter &filter, ::K9::Image &imageOut)const;*/
		};
	}
}

#endif // !_IMAGEOPERATIONS_H_
