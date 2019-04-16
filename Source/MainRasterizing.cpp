#define _USE_MATH_DEFINES

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <algorithm>
#include <Camera.h>
#include <DrawLineRasterizationCommand.h>
#include <DrawTriangleRasterizationCommand.h>
#include <GeometryFactory.h>
#include <GraphicsPipeline.h>
#include <IRasterizationCommand.h>
#include <Light.h>
#include <Material.h>
#include <math.h>
#include <MatrixFactory.h>
#include <memory>
#include <PerspectiveCamera.h>
#include <SolidMaterialColor.h>
#include <string>
#include <vector>
#include <Vertex.h>
#include <VertexProcessingStageCommand.h>

void addMesh(K9::Geometry::Geometry& mesh);
void addMeshWireframe(K9::Geometry::Geometry& mesh);

int main() {
	using namespace K9;

	Renderer::Window window;

	char *name = "Rasterizer";
	float width = 1366;
	float height = 768;

	float hipo = 271.0f / cosf(M_PI_4);
	float height_2 = sinf(M_PI_4)* hipo;
	float width_2 = height_2 * width / height;

	window.name = name;
	//window.width = width;
	//window.height = height;
	window.width = width_2*2.0f;
	window.height = height_2*2.0f;

	Renderer renderer(window);

	Camera::ImagePlane imagePlane = { -width_2, -height_2, width_2 * 2, height_2 * 2 };
	//Camera::ImagePlane imagePlane = { -width/2, -height/2, width , height  };
	Camera *camera = new PerspectiveCamera(Vector3(0, 0, 0), Vector3(0, 1, 0), -Vector3(0.0f, 0.0f, 1.0f), imagePlane, -271.0f);

	Light light(Vector3(-150.0f, 150.0f, -250), Vector3(1.0f, 1.0f, 1.0f));
	Light light2(Vector3(-200.0f, 200.0f, -100), Vector3(0.8f, 0.8f, 0.8f));
	K9::Color ambientLight(0.6f, 0.6f, 0.6f);

	::K9::Geometry::Geometry sphere1 = ::K9::Geometry::GeometryFactory::sphere(200, 55, 55);
	sphere1.position = Vector4(0.0f, 0.0f, -300.0f, 1.0f);
	sphere1.material = Material(Vector4(0.5f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector4(0.8f, 0.8f, 0.8f, 1.0f), 70, Vector4(0.0f, 0.0f, 0.0f, 1.0f));
	
	::K9::Geometry::Geometry sphere2 = ::K9::Geometry::GeometryFactory::sphere(200, 55, 55);
	sphere2.position = Vector4(600.0f, 90.0f, -400.0f, 1.0f);
	sphere2.material = Material(Vector4(0.5f, 0.0f, 0.0f, 1.0f), Vector4(1.0f, 0.0f, 0.0f, 1.0f), Vector4(0.5f, 0.5f, 0.5f, 1.0f), 100, Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	//Geometry::Geometry plane1 = Geometry::GeometryFactory::plane(1000, 1000, 10);
	//Geometry::Geometry plane2 = Geometry::GeometryFactory::plane(1000, 1000, 5);

	std::shared_ptr<GraphicsPipeline::GraphicsPipeline> gp = GraphicsPipeline::GraphicsPipeline::getInstance().lock();
	
	if (gp != nullptr) {
		gp->ambientLight() = ambientLight;
		//gp->lights().push_back(light);
		gp->lights().push_back(light2);

		gp->setRenderer(std::make_shared<Renderer>(renderer));
		gp->setCamera(camera);
		gp->setCameraTransformation(MatrixFactory::cameraTransformation(camera->u(), camera->v(), camera->w(), camera->position()));
		gp->setProjectionTransformation(MatrixFactory::perspectiveTransformation(imagePlane.left, imagePlane.bottom, -150, imagePlane.width + imagePlane.left, imagePlane.height + imagePlane.bottom, -1000));
		gp->setViewportTransformation(MatrixFactory::viewportTransformation(imagePlane.width, imagePlane.height));
		
		gp->vertexProcessingStageCommand() = std::make_shared<GraphicsPipeline::VertexProcessingStageCommand>(GraphicsPipeline::VertexProcessingStageCommand());

		addMesh(sphere1);
		addMeshWireframe(sphere2);

		
		/*
		Vertex v1;
		v1.setPropertyByName("position", Vector4(500, 200, 200, 1));
		v1.setPropertyByName("color", Vector4(1, 1, 1, 1));
		vertexes.push_back(v1);

		Vertex v2;
		v2.setPropertyByName("position", Vector4(-10, 0, 200, 1));
		v2.setPropertyByName("color", Vector4(0, 0, 0, 0));
		vertexes.push_back(v2);

		rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(0, 1, 0));

		v1.setPropertyByName("position", Vector4(-10, 0, 200, 1));
		v1.setPropertyByName("color", Vector4(1, 1, 1, 1));
		vertexes.push_back(v1);

		v2.setPropertyByName("position", Vector4(500, -200, 200, 1));
		v2.setPropertyByName("color", Vector4(0, 0, 0, 0));
		vertexes.push_back(v2);

		rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(2, 3, 0));

		v1.setPropertyByName("position", Vector4(-10, 0, 200, 1));
		v1.setPropertyByName("color", Vector4(1, 1, 1, 1));
		vertexes.push_back(v1);

		v2.setPropertyByName("position", Vector4(10, 300, 200, 1));
		v2.setPropertyByName("color", Vector4(0, 0, 0, 0));
		vertexes.push_back(v2);

		rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(4, 5, 0));

		v1.setPropertyByName("position", Vector4(0, 0, 200, 1));
		v1.setPropertyByName("color", Vector4(1, 1, 1, 1));
		vertexes.push_back(v1);

		v2.setPropertyByName("position", Vector4(10, -250, 200, 1));
		v2.setPropertyByName("color", Vector4(0, 0, 0, 0));
		vertexes.push_back(v2);

		rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(6, 7, 0));
		*/
		gp->execute();
		gp->getRenderer()->show(0, 0);
	}
	
	cv::waitKey();

	delete camera;

	return 0;
}

void addMesh(K9::Geometry::Geometry& mesh) {
	using namespace K9;
	auto gp = GraphicsPipeline::GraphicsPipeline::getInstance().lock();
	if (gp != nullptr) {
		std::vector<Vertex> &vertexes = gp->getVertexes();
		std::vector<std::shared_ptr<GraphicsPipeline::IRasterizationCommand> > &rasterizationCommands = gp->rasterizationCommands();

		for (int i = 0; i < mesh.conections.size() - 2; i += 3) {
			rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawTriangleRasterizationCommand>(mesh.conections[i], mesh.conections[i + 1], mesh.conections[i + 2], vertexes.size()));
		}
		Matrix4 moveMat = MatrixFactory::move(mesh.position[0], mesh.position[1], mesh.position[2]);
		for (auto it = mesh.vertexes.begin(); it != mesh.vertexes.end(); ++it) {
			//it->setPropertyByName("ka", Vector4(sphere1.material.ambientCoefficient()->colorAt(0,0), 0.0f));
			//it->setPropertyByName("kd", Vector4(sphere1.material.diffuseCoefficient()->colorAt(0, 0), 0.0f));
			//it->setPropertyByName("ks", Vector4(sphere1.material.specularCoefficient()->colorAt(0, 0), 0.0f));
			//it->setPropertyByName("p", Vector4(sphere1.material.phongExponent(), sphere1.material.phongExponent(), sphere1.material.phongExponent(), sphere1.material.phongExponent()));
			//it->setPropertyByName("km", Vector4(sphere1.material.mirrorReflection()->colorAt(0, 0), 0.0f));
			it->setMaterial(mesh.material);
			it->setPropertyByName("position", moveMat*(*it->getPropertyByName("position")));
		}
		vertexes.insert(std::end(vertexes), std::begin(mesh.vertexes), std::end(mesh.vertexes));
	}
}

void addMeshWireframe(K9::Geometry::Geometry& mesh) {
	using namespace K9;
	auto gp = GraphicsPipeline::GraphicsPipeline::getInstance().lock();
	if (gp != nullptr) {
		std::vector<Vertex> &vertexes = gp->getVertexes();
		std::vector<std::shared_ptr<GraphicsPipeline::IRasterizationCommand> > &rasterizationCommands = gp->rasterizationCommands();

		for (int i = 0; i < mesh.conections.size() - 2; i += 3) {
			rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(mesh.conections[i], mesh.conections[i + 1], vertexes.size()));
			rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(mesh.conections[i + 1], mesh.conections[i + 2], vertexes.size()));
			rasterizationCommands.push_back(std::make_shared<GraphicsPipeline::DrawLineRasterizationCommand>(mesh.conections[i + 2], mesh.conections[i], vertexes.size()));
		}
		Matrix4 moveMat = MatrixFactory::move(mesh.position[0], mesh.position[1], mesh.position[2]);
		for (auto it = mesh.vertexes.begin(); it != mesh.vertexes.end(); ++it) {
			/*it->setPropertyByName("ka", Vector4(sphere2.material.ambientCoefficient()->colorAt(0, 0), 0.0f));
			it->setPropertyByName("kd", Vector4(sphere2.material.diffuseCoefficient()->colorAt(0, 0), 0.0f));
			it->setPropertyByName("ks", Vector4(sphere2.material.specularCoefficient()->colorAt(0, 0), 0.0f));
			it->setPropertyByName("p", Vector4(sphere2.material.phongExponent(), sphere2.material.phongExponent(), sphere2.material.phongExponent(), sphere2.material.phongExponent()));
			it->setPropertyByName("km", Vector4(sphere2.material.mirrorReflection()->colorAt(0, 0), 0.0f));*/
			it->setMaterial(mesh.material);
			it->setPropertyByName("position", moveMat*(*it->getPropertyByName("position")));
		}
		vertexes.insert(std::end(vertexes), std::begin(mesh.vertexes), std::end(mesh.vertexes));
	}
}