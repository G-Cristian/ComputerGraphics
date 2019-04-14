#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <AbstractMaterialColor.h>
#include <memory>
#include <SolidMaterialColor.h>

namespace K9 {

	class Material {
	public:
		using Color = AbstractMaterialColor::Color;
		Material() :
			Material(SolidMaterialColor(), SolidMaterialColor(), SolidMaterialColor(), 0.0f, SolidMaterialColor()) {
		}

		Material(const Color& ka, const Color&kd, const Color &ks, float p, const Color &km) :
			Material(SolidMaterialColor(ka), SolidMaterialColor(kd), SolidMaterialColor(ks), p, SolidMaterialColor(km)) {
		}

		Material(const AbstractMaterialColor &ka, const AbstractMaterialColor &kd, const AbstractMaterialColor &ks, float p, const AbstractMaterialColor &km) :
			_ka(ka.clone()),
			_kd(kd.clone()),
			_ks(ks.clone()),
			_p(p),
			_km(km.clone()) {
		}

		//getters
		const std::shared_ptr<AbstractMaterialColor> ambientCoefficient() const { return _ka; }
		std::shared_ptr<AbstractMaterialColor> ambientCoefficient() { return _ka; }
		const std::shared_ptr<AbstractMaterialColor> diffuseCoefficient() const { return _kd; }
		std::shared_ptr<AbstractMaterialColor> diffuseCoefficient() { return _kd; }
		const std::shared_ptr<AbstractMaterialColor> specularCoefficient() const { return _ks; }
		std::shared_ptr<AbstractMaterialColor> specularCoefficient() { return _ks; }
		const float& phongExponent() const { return _p; }
		float& phongExponent() { return _p; }
		const std::shared_ptr<AbstractMaterialColor> mirrorReflection() const { return _km; }
		std::shared_ptr<AbstractMaterialColor> mirrorReflection() { return _km; }

	private:
		std::shared_ptr<AbstractMaterialColor> _ka;			//Ambient coefficient
		std::shared_ptr<AbstractMaterialColor> _kd;			//Diffuse coefficient
		std::shared_ptr<AbstractMaterialColor> _ks;			//Specular coefficient
		float _p;			//Phong exponent
		std::shared_ptr<AbstractMaterialColor> _km;			//Mirror reflection
	};

}

#endif // !_MATERIAL_H_
