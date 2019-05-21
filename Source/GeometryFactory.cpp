#include <cmath>
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
			vertex.setPropertyByName("textureCoord", Vector4((3.14f + std::atan2f(radius, 0.0f))/(2.0f*3.14f), (3.14f - std::acosf(0.0f)) / (3.14f), 0.0f, 0.0f));
			geometry.vertexes.push_back(vertex);

			float stepsHeightSize = 2.0f * radius / static_cast<float>(stepsHight);
			float stepsCircumferenceSize = 6.28f / static_cast<float>(stepsCircumference);
			for (int i = 1; i < stepsHight - 1; ++i) {
				for (int j = 0; j < stepsCircumference; ++j) {
					vertex = Vertex();
					float x = radius*cosf(j*stepsCircumferenceSize)*sinf(i*3.14f / stepsHight);
					float y = radius*cosf(i*3.14f / stepsHight)/*radius-i*stepsHeightSize*/;
					float z = radius*sinf(j*stepsCircumferenceSize)*sinf(i*3.14f / stepsHight);
					vertex.setPropertyByName("position", Vector4(x, y, z, 1.0f));
					vertex.setPropertyByName("color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
					vertex.setPropertyByName("normal", Vector4(x, y, z, 0.0f).normalize());
					vertex.setPropertyByName("textureCoord", Vector4((3.14f + std::atan2f(y, x)) / (2.0f * 3.14f), (3.14f - std::acosf(z/Vector4(x,y,z, 0.0f).norm())) / (3.14f), 0.0f, 0.0f));
					geometry.vertexes.push_back(vertex);
				}
			}

			vertex = Vertex();
			vertex.setPropertyByName("position", Vector4(0.0f, -radius, 0.0f, 1.0f));
			vertex.setPropertyByName("color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
			vertex.setPropertyByName("normal", Vector4(0.0f, -1.0f, 0.0f, 0.0f));
			vertex.setPropertyByName("textureCoord", Vector4((3.14f + std::atan2f(-radius, 0.0f)) / (2.0f * 3.14f), (3.14f - std::acosf(0.0f)) / (3.14f), 0.0f, 0.0f));
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

		Geometry GeometryFactory::plane(float width, float height, int steps) {
			Geometry geometry;
			
			float halfWidth = width / 2.0f;
			float halfHeight = height / 2.0f;
			float stepsWidthSize = width / static_cast<float>(steps);
			float stepsHeightSize = height / static_cast<float>(steps);
			for (int i = 0; i <= steps; ++i) {
				float l = -halfWidth + i*stepsWidthSize;
				for (int j = 0; j <= steps; ++j) {
					Vertex vertex;
					float r = -halfHeight + j*stepsHeightSize;
					vertex.setPropertyByName("position", Vector4(l, 0.0f, r, 1.0f));
					vertex.setPropertyByName("color", Vector4(1.0f, 0.0f, 0.0f, 1.0f));
					vertex.setPropertyByName("normal", Vector4(0.0f, 1.0f, 0.0f, 0.0f));
					vertex.setPropertyByName("textureCoord", Vector4(l, r,0.0f,0.0f));

					geometry.vertexes.push_back(vertex);
				}
			}

			for (int j = 0; j < steps; ++j) {
				for (int i = 0; i < steps; ++i) {
					int c = i + j*(steps+1);
					geometry.conections.push_back(c);
					geometry.conections.push_back(c + 1);
					geometry.conections.push_back(c + steps + 2);
					geometry.conections.push_back(c);
					geometry.conections.push_back(c + steps + 2);
					geometry.conections.push_back(c + steps + 1);
				}
			}

			return geometry;
		}
	}
}