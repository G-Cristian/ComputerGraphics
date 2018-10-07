#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <Vector3.h>

namespace K9 {

	typedef Vector3 Color;

	class Material {
	public:
		Material(const Color &ka, const Color &kd, const Color &ks, float p, const Color &km) :
			_ka(ka),
			_kd(kd),
			_ks(ks),
			_p(p),
			_km(km) {
		}

		//getters
		const Color& ambientCoefficient() const { return _ka; }
		Color& ambientCoefficient() { return _ka; }
		const Color& diffuseCoefficient() const { return _kd; }
		Color& diffuseCoefficient() { return _kd; }
		const Color& specularCoefficient() const { return _ks; }
		Color& specularCoefficient() { return _ks; }
		const float& phongExponent() const { return _p; }
		float& phongExponent() { return _p; }
		const Color& mirrorReflection() const { return _km; }
		Color& mirrorReflection() { return _km; }

	private:
		Color _ka;			//Ambient coefficient
		Color _kd;			//Diffuse coefficient
		Color _ks;			//Specular coefficient
		float _p;			//Phong exponent
		Color _km;			//Mirror reflection
	};

}

#endif // !_MATERIAL_H_
