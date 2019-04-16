#ifndef _VERTEX_H_
#define _VERTEX_H_

#include <Vector4.h>
#include <map>
#include <Material.h>
#include <string>

namespace K9 {
	class Vertex {
		typedef std::map<std::string, Vector4> PropertiesType;
	public:
		//default constructor
		Vertex() :
			_properties(new PropertiesType()) {
		}

		//copy constructor
		Vertex(const Vertex &other) :
			_properties(new PropertiesType()),
			_material(other._material){
			(*_properties) = *other._properties;
		}

		//move constructor
		Vertex(Vertex &&other) noexcept :
		_properties(other._properties),
		_material(std::move(other._material)) {
			other._properties = nullptr;
			other._material = nullptr;
		}

		//destructor
		~Vertex() {
			delete _properties;
			_properties = nullptr;
			_material = nullptr;
		}

		//copy assignment operator
		Vertex& operator=(const Vertex &other) {
			PropertiesType *aux = new PropertiesType();
			delete _properties;
			(*aux) = *other._properties;
			_properties = aux;
			_material = other._material;

			return *this;
		}

		//move assignment operator
		Vertex& operator=(Vertex &&other) noexcept {
			if (this != &other) {
				delete _properties;
				_properties = other._properties;
				other._properties = nullptr;
				_material = std::move(other._material);
				other._material = nullptr;
			}

			return *this;
		}

		//getters
		const Vector4* getPropertyByName(const std::string &propertyName) const {
			Vector4 *ret = nullptr;
			auto it = _properties->find(propertyName);
			if (it != _properties->end()) {
				ret = &(it->second);
			}

			return ret;
		}

		Vector4* getPropertyByName(const std::string &propertyName) {
			Vector4 *ret = nullptr;
			auto it = _properties->find(propertyName);
			if (it != _properties->end()) {
				ret = &(it->second);
			}

			return ret;
		}

		const std::shared_ptr<const Material> getMaterial() const {
			return _material;
		}

		//setters
		void setPropertyByName(const std::string &propertyName, const Vector4 &value) {
			(*_properties)[propertyName] = value;
		}

		void setMaterial(const Material& material) {
			_material = std::shared_ptr<Material>(new Material(material));
		}

		void setMaterial(Material&& material) {
			_material = std::shared_ptr<Material>(new Material(std::move(material)));
		}
	private:
		PropertiesType *_properties;
		std::shared_ptr<Material> _material;
	};
}

#endif // !_VERTEX_H_
