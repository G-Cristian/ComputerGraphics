#ifndef _GEOMETRYFACTORY_H_
#define _GEOMETRYFACTORY_H_

#include <Material.h>
#include <vector>
#include <Vector4.h>
#include <Vertex.h>

namespace K9 {
	namespace Geometry {
		struct Geometry {
			Vector4 position;
			Material material;
			std::vector<Vertex> vertexes;
			std::vector<int> conections;
		};

		class GeometryFactory {
		public:
			static Geometry sphere(float radius, int stepsHight, int stepsCircumference);
			static Geometry plane(float width, float height, int steps);
		private:
			GeometryFactory() = delete;
			~GeometryFactory() = delete;
			GeometryFactory(const GeometryFactory &other) = delete;
			GeometryFactory& operator=(const GeometryFactory &other) = delete;
		};
	}
}

#endif // !_GEOMETRYFACTORY_H_
