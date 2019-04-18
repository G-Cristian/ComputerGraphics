#ifndef _SOLIDMATERIALCOLOR_H_
#define _SOLIDMATERIALCOLOR_H_

#include <AbstractMaterialColor.h>

namespace K9 {
	class SolidMaterialColor :public AbstractMaterialColor {
	public:
		using Color = AbstractMaterialColor::Color;
		SolidMaterialColor()=default;
		SolidMaterialColor(float x, float y, float z, float w) :
			_color(Vector4(x,y,z,w)) {
		}
		SolidMaterialColor(const Color &color):
			_color(color){
		}
		SolidMaterialColor(Color &&color) noexcept :
			_color(std::move(color)) {
		}

		SolidMaterialColor(const SolidMaterialColor &other) = default;
		SolidMaterialColor(SolidMaterialColor &&other) noexcept :
		AbstractMaterialColor(std::move(other)),
		_color(std::move(other._color)){
		}

		SolidMaterialColor& operator=(const SolidMaterialColor &other) {
			AbstractMaterialColor::operator=(other);
			_color = other._color;
			return *this;
		}

		SolidMaterialColor& operator=(SolidMaterialColor &&other) {
			if (this != &other) {
				AbstractMaterialColor::operator=(std::move(other));
				_color = std::move(other._color);
			}
			return *this;
		}

		virtual ~SolidMaterialColor() = default;

		Color colorAt(float u, float v) const override final {
			return _color;
		}

		SolidMaterialColor* clone() const override final {
			return new SolidMaterialColor(*this);
		}
	private:
		Color _color;
	};
}

#endif // !_SOLIDMATERIALCOLOR_H_
