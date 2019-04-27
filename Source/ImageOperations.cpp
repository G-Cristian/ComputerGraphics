#include <algorithm>
#include <Color.h>
#include <ImageOperations.h>
#include <math.h>

namespace K9 {
	namespace Images {
		::K9::Image ImageOperations::applyFilter(const ::K9::Image &img, ::K9::Filter *filter, float scale /*= 1.0f*/) {
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
					float maxJp = std::min(static_cast<unsigned int>(j + r), ny - 1);
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

						red += SR[ip] * filterValue;
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

		::K9::Image ImageOperations::resample(const ::K9::Image &imageIn, float newWidth, float newHeight, const ::K9::Filter &filter)const {
			return resample(imageIn, -0.5f, imageIn.getWidth() - 0.5f, -0.5f, imageIn.getHeight() - 0.5f, newWidth, newHeight, filter);
		}

		::K9::Image ImageOperations::resample(const ::K9::Image &imageIn, float xl, float xh, float yl, float yh, float newWidth, float newHeight, const ::K9::Filter &filter)const {
			Image newImage = resampleRows(imageIn, xl, xh, yl, yh, newWidth, yh - yl, filter);
			//return newImage;
			return resampleColumns(newImage, -0.5f , newImage.getWidth() - 0.5f, -0.5f, newImage.getHeight() -0.5f, newWidth, newHeight, filter);
		}

		::K9::Image ImageOperations::resampleRows(const ::K9::Image &imageIn, float xl, float xh, float yl, float yh, float newWidth, float newHeight, const ::K9::Filter &filter)const {
			Image newImage(newWidth, newHeight);
			auto itOther = newImage.rowInter(0);
			auto end = imageIn.rowInter(static_cast<int>(std::ceil(yh)));

			for (auto it = imageIn.rowInter(static_cast<int>(std::ceil(yl))); it != end; ++it){
				resampleSec(it, xh-xl, xl, xh, newWidth, filter, itOther);
				++itOther;
			}

			return newImage;
		}

		::K9::Image ImageOperations::resampleColumns(const ::K9::Image &imageIn, float xl, float xh, float yl, float yh, float newWidth, float newHeight, const ::K9::Filter &filter)const {
			Image newImage(newWidth, newHeight);
			auto itOther = newImage.columnI(0);
			auto end = imageIn.columnI(static_cast<int>(std::ceil(xh)));

			for (auto it = imageIn.columnI(static_cast<int>(std::ceil(xl))); it != end; ++it) {
				resampleSec(it, yh - yl, yl, yh, newHeight, filter, itOther);
				++itOther;
			}

			return newImage;
		}

		void ImageOperations::resampleSec(::K9::Image::IIterator &itIn, int size, float l, float h, int newLenght, const ::K9::Filter &filter, ::K9::Image::IIterator &itOut) const {
			float r = filter.getRadius();
			float dx = (h - l) / (float)(newLenght);
			float x0 = l + dx / 2.0f;
			for (size_t i = 0; i < newLenght; ++i) {
				float filterValueSum = 0.0f;
				float red = 0.0f;
				float green = 0.0f;
				float blue = 0.0f;
				float x = x0 + (float)(i)*dx;

				for (size_t j = std::max(static_cast<int>(ceilf(x - r)), 0); j <= std::min(static_cast<int>(x + r), size-1); ++j) {
					float filterValue = filter.executeScaled(x - j, 1.0f);
					filterValueSum += filterValue;
					Image::ElementsType color = itIn.at(j);
					red += getRedColor32(color) * filterValue;
					green += getGreenColor32(color) * filterValue;
					blue += getBlueColor32(color) * filterValue;
				}

				red = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(red / filterValueSum))));
				green = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(green / filterValueSum))));
				blue = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(blue / filterValueSum))));

				K9::Color32 color = K9::setColor32(red, green, blue, 255);

				itOut.at(i) = color;
			}
		}

		//void ImageOperations::resampleRowI(const ::K9::Image &imageIn, int rowI, float l, float h, float newLenght, const ::K9::Filter &filter, ::K9::Image &imageOut)const {
		//	float r = filter.getRadius();
		//	float dx = (h - l) / newLenght;
		//	float x0 = l + dx / 2.0f;
		//	for (size_t i = 0; i < newLenght; ++i) {
		//		float filterValueSum = 0.0f;
		//		float red = 0.0f;
		//		float green = 0.0f;
		//		float blue = 0.0f;
		//		float x = x0 + (float)(i)*dx;

		//		for (size_t j = std::max(static_cast<int>(ceilf(x - r)), 0); j < std::min(static_cast<unsigned int>(x + r), imageIn.getWidth()); ++j) {
		//			float filterValue = filter.executeScaled(x-j, 1.0f);
		//			filterValueSum += filterValue;
		//			Image::ElementsType color = imageIn.getColorAtXY(j, rowI);
		//			red += red + getRedColor32(color) * filterValue;
		//			green += green + getGreenColor32(color) * filterValue;
		//			blue += blue + getBlueColor32(color) * filterValue;
		//		}

		//		red = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(red / filterValueSum))));
		//		green = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(green / filterValueSum))));
		//		blue = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(blue / filterValueSum))));

		//		K9::Color32 color = K9::setColor32(red, green, blue, 255);

		//		//TODO: saturate colors to their max if necesary
		//		imageOut.setColorAtXY(color, i, rowI);
		//	}
		//}

		//void ImageOperations::resampleColumnI(const ::K9::Image &imageIn, int columnI, float l, float h, float newLenght, const ::K9::Filter &filter, ::K9::Image &imageOut)const {
		//	float r = filter.getRadius();
		//	float dx = (h - l) / newLenght;
		//	float x0 = l + dx / 2.0f;
		//	for (size_t i = 0; i < newLenght; ++i) {
		//		float filterValueSum = 0.0f;
		//		float red = 0.0f;
		//		float green = 0.0f;
		//		float blue = 0.0f;
		//		float x = x0 + (float)(i)*dx;

		//		for (size_t j = std::max(static_cast<int>(ceilf(x - r)), 0); j < std::min(static_cast<unsigned int>(x + r), imageIn.getHeight()); ++j) {
		//			float filterValue = filter.executeScaled(x - j, 1.0f);
		//			filterValueSum += filterValue;
		//			Image::ElementsType color = imageIn.getColorAtXY(columnI, j);
		//			red += red + getRedColor32(color) * filterValue;
		//			green += green + getGreenColor32(color) * filterValue;
		//			blue += blue + getBlueColor32(color) * filterValue;
		//		}

		//		red = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(red / filterValueSum))));
		//		green = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(green / filterValueSum))));
		//		blue = static_cast<K9::uchar>(std::max(0, std::min(255, static_cast<int>(blue / filterValueSum))));

		//		K9::Color32 color = K9::setColor32(red, green, blue, 255);
		//		
		//		//TODO: saturate colors to their max if necesary
		//		imageOut.setColorAtXY(color, columnI, i);
		//	}
		//}
	}
}