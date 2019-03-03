#include <GeometryFactory.h>
#include <math.h>
#include <Vector4.h>
#include <Vertex.h>

namespace K9 {
	namespace Geometry {
		Geometry GeometryFactory::sphere(float radius, int stepsHight, int stepsCircumference) {
			Geometry geometry;
			Vertex vertex;
			vertex.setPropertyByName("position", Vector4(0.0f, radius, 0.0f, 1.0f));
			vertex.setPropertyByName("color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			vertex.setPropertyByName("normal", Vector4(0.0f, 1.0f, 0.0f, 0.0f));
			geometry.vertexes.push_back(vertex);

			float stepsHeightSize = 2.0f * radius / static_cast<float>(stepsHight);
			float stepsCircumferenceSize = 6.28f / static_cast<float>(stepsCircumference);
			for (int i = 1; i < stepsHight - 1; ++i) {
				for (int j = 0; j < stepsCircumference; ++j) {
					vertex = Vertex();
					vertex.setPropertyByName("position", Vector4(radius*cosf(j*stepsCircumferenceSize)*sinf(i*3.14f/stepsHight), radius*cosf(i*3.14f / stepsHight)/*radius-i*stepsHeightSize*/, radius*sinf(j*stepsCircumferenceSize)*sinf(i*3.14f / stepsHight), 1.0f));
					vertex.setPropertyByName("color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
					vertex.setPropertyByName("normal", Vector4(radius*cosf(j*stepsCircumferenceSize)*sinf(i*3.14f / stepsHight), radius*cosf(i*3.14f / stepsHight)/*radius-i*stepsHeightSize*/, radius*sinf(j*stepsCircumferenceSize)*sinf(i*3.14f / stepsHight), 0.0f).normalize());
					geometry.vertexes.push_back(vertex);
				}
			}

			vertex = Vertex();
			vertex.setPropertyByName("position", Vector4(0.0f, -radius, 0.0f, 1.0f));
			vertex.setPropertyByName("color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			vertex.setPropertyByName("normal", Vector4(0.0f, -1.0f, 0.0f, 0.0f));
			geometry.vertexes.push_back(vertex);

			int current = 0;
			for (int j = 0; j < stepsCircumference-1; ++j) {
				geometry.conections.push_back(0);
				geometry.conections.push_back(j+1);
				geometry.conections.push_back(j+2);
			}
			current += 1;

			for (int i = 1; i < stepsHight - 2; ++i) {
				for (int j = 0; j < stepsCircumference; ++j) {
					geometry.conections.push_back(current);
					geometry.conections.push_back(current + stepsCircumference);
					geometry.conections.push_back(current + stepsCircumference + 1);
					geometry.conections.push_back(current);
					geometry.conections.push_back(current + stepsCircumference+1);
					geometry.conections.push_back(current + 1);
					++current;
				}
			}

			int n = geometry.vertexes.size() - 1;
			for (int j = 0; j < stepsCircumference - 1; ++j) {
				geometry.conections.push_back(current);
				geometry.conections.push_back(n);
				geometry.conections.push_back(current + 1);
				++current;
			}

			return geometry;
		}
	}
}