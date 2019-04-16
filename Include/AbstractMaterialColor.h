#ifndef _ABSTRACTMATERIALCOLOR_H_
#define _ABSTRACTMATERIALCOLOR_H_

#include <Vector4.h>

namespace K9 {
	class AbstractMaterialColor {
	public:
		typedef Vector4 Color;

		virtual ~AbstractMaterialColor() = default;

		virtual Color colorAt(float u, float v) const = 0;
		virtual AbstractMaterialColor* clone() const = 0;
	protected:
		AbstractMaterialColor() = default;
		AbstractMaterialColor(const AbstractMaterialColor &) = default;
		AbstractMaterialColor(AbstractMaterialColor && other) noexcept = default;

		AbstractMaterialColor& operator=(const AbstractMaterialColor &other) = default;
		AbstractMaterialColor& operator=(AbstractMaterialColor &&other) noexcept = default;
	};
}

#endif // !_ABSTRACTMATERIALCOLOR_H_
