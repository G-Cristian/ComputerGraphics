#ifndef _ABSTRACTMATERIALCOLOR_H_
#define _ABSTRACTMATERIALCOLOR_H_

#include <Vector3.h>

namespace K9 {
	class AbstractMaterialColor {
	public:
		typedef Vector3 Color;

		virtual ~AbstractMaterialColor() = default;

		virtual const Color& colorAt(const Vector3 &coordinate) const = 0;
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
