#ifndef _TEXTUREMATERIALCOLOR_H_
#define _TEXTUREMATERIALCOLOR_H_

#include <AbstractMaterialColor.h>
#include <Image.h>

namespace K9 {
	class TextureMaterialColor :public AbstractMaterialColor {
	public:
		using Color = AbstractMaterialColor::Color;
		TextureMaterialColor(const Image &image) :
			_image(image) {
		}
		TextureMaterialColor(Image &&image) noexcept:
			_image(std::move(image)) {
		}

		TextureMaterialColor(const TextureMaterialColor &other) = default;
		TextureMaterialColor(TextureMaterialColor &&other) noexcept :
		AbstractMaterialColor(std::move(other)),
			_image(std::move(other._image)) {
		}

		TextureMaterialColor& operator=(const TextureMaterialColor &other) {
			AbstractMaterialColor::operator=(other);
			_image = other._image;
			return *this;
		}

		TextureMaterialColor& operator=(TextureMaterialColor &&other) {
			if (this != &other) {
				AbstractMaterialColor::operator=(std::move(other));
				_image = std::move(other._image);
			}
			return *this;
		}

		virtual ~TextureMaterialColor() = default;

		Color colorAt(float u, float v) const override final {
			int i = roundf(u*_image.getWidth() - 0.5f);
			int j = roundf(v*_image.getHeight() - 0.5f);
			Color32 color = _image.getColorAtXY(i, j);
			return (Color(getRedColor32(color), getGreenColor32(color), getBlueColor32(color), getAlphaColor32(color))/255.0f);
		}

		TextureMaterialColor* clone() const override final {
			return new TextureMaterialColor(*this);
		}
	private:
		Image _image;
	};
}

#endif // !_TEXTUREMATERIALCOLOR_H_
