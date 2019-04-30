#ifndef _TEXTUREMATERIALCOLOR_H_
#define _TEXTUREMATERIALCOLOR_H_

#include <AbstractMaterialColor.h>
#include <algorithm>
#include <Image.h>
#include <iostream>

namespace K9 {
	class TextureMaterialColor :public AbstractMaterialColor {
	public:
		enum TextureLookUpMethod { /*NORMAL,*/ CLAMP, WRAP };
		using Color = AbstractMaterialColor::Color;
		TextureMaterialColor(const Image &image, TextureLookUpMethod textureLookUpMethod = TextureLookUpMethod::CLAMP) :
			_image(image),
			_textureLookUpMethod(textureLookUpMethod){
		}
		TextureMaterialColor(Image &&image, TextureLookUpMethod textureLookUpMethod = TextureLookUpMethod::CLAMP) noexcept:
			_image(std::move(image)),
			_textureLookUpMethod(textureLookUpMethod) {
		}

		TextureMaterialColor(const TextureMaterialColor &other) = default;
		TextureMaterialColor(TextureMaterialColor &&other) noexcept :
		AbstractMaterialColor(std::move(other)),
			_image(std::move(other._image)),
			_textureLookUpMethod(other._textureLookUpMethod){
		}

		TextureMaterialColor& operator=(const TextureMaterialColor &other) {
			AbstractMaterialColor::operator=(other);
			_image = other._image;
			_textureLookUpMethod = other._textureLookUpMethod;
			return *this;
		}

		TextureMaterialColor& operator=(TextureMaterialColor &&other) {
			if (this != &other) {
				AbstractMaterialColor::operator=(std::move(other));
				_image = std::move(other._image);
				_textureLookUpMethod = other._textureLookUpMethod;
			}
			return *this;
		}

		virtual ~TextureMaterialColor() = default;

		Color colorAt(float u, float v) const override final {
			int i = roundf(u*static_cast<float>(_image.getWidth()) - 0.5f);
			int j = roundf(v*static_cast<float>(_image.getHeight()) - 0.5f);

			//if (j == 514) {
			//	std::cout << "v: " << v << std::endl;
			//}
			//std::cout << "u: " << u << ", v: " << v << ", i: " << i << ", j: " << j << std::endl;
			if (_textureLookUpMethod == TextureLookUpMethod::CLAMP) {
				i = std::max(0, std::min(i, static_cast<int>(_image.getWidth()-1)));
				j = std::max(0, std::min(j, static_cast<int>(_image.getHeight() - 1)));
			}
			else if(_textureLookUpMethod == TextureLookUpMethod::WRAP) {
				i = i % _image.getWidth();
				j = j % _image.getHeight();
			}

			Color32 color = _image.getColorAtXY(i, j);
			return (Color(getRedColor32(color), getGreenColor32(color), getBlueColor32(color), getAlphaColor32(color))/255.0f);
		}

		TextureMaterialColor* clone() const override final {
			return new TextureMaterialColor(*this);
		}
	private:
		Image _image;
		TextureLookUpMethod _textureLookUpMethod = TextureLookUpMethod::CLAMP;
	};
}

#endif // !_TEXTUREMATERIALCOLOR_H_
