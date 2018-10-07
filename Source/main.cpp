#define _USE_MATH_DEFINES

#include <algorithm>
#include <Camera.h>
#include <Light.h>
#include <math.h>
#include <memory>
#include <PerspectiveCamera.h>
#include <Plane.h>
#include <Point2D.h>
#include <Ray.h>
#include <renderer.h>
#include <Sphere.h>
#include <string>
#include <Surface.h>
#include <vector>

void draw(K9::Renderer &renderer, const std::vector<K9::Surface*> &objects, const K9::Camera *camera, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight);
K9::Color rayColor(const K9::Ray &ray, float t0, float t1, const vector<K9::Surface*> &objects, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight, int recursionDepth);
bool isShadowed(const K9::Vector3 &origin, float t0, float t1, const vector<K9::Surface*> &objects, const K9::Light *light);
inline K9::Vector3 getMirrorReflectionDirection(const K9::Vector3 &viewDirection, const K9::Vector3 &surfaceNormal);

int main() {
	using namespace K9;
	Renderer::Window window;

	window.name = "RayTracer";
	window.width = 1366;
	window.height= 768;
	Renderer renderer(window);
	
	//Camera::ImagePlane imagePlane = { -window.width / 2, -window.height / 2, window.width, window.height };
	float hipo = 150.0f / cosf(M_PI_4);
	float hight_2 = sinf(M_PI_4)* hipo;
	float width_2 = hight_2 * window.width / window.height;

	Camera::ImagePlane imagePlane = { -width_2, -hight_2, width_2 * 2, hight_2 * 2 };
	Camera *camera = new PerspectiveCamera(Vector3(0,0,0), Vector3(0, 1, 0), -Vector3(0, 0, 1), imagePlane, 150);
	Material sMaterial1(Vector3(0.5f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.8f, 0.8f, 0.8f), 70, Vector3(0.0f, 0.0f, 0.0f));
	Material sMaterial2(Vector3(0.5f, 0.0f, 0.0f), Vector3(1.0f, 0.0f, 0.0f), Vector3(0.5f, 0.5f, 0.5f), 100, Vector3(0.2f, 0.2f, 0.2f));
	Material pMaterial(Vector3(0.3f, 0.3f, 0.3f), Vector3(0.5f, 0.5f, 0.5f), Vector3(1.0f, 1.0f, 1.0f), 10000, Vector3(1.0f, 1.0f, 1.0f));
	Material pMaterial2(Vector3(0.8f, 0.8f, 0.8f), Vector3(0.1f, 0.1f, 0.1f), Vector3(1.0f, 1.0f, 1.0f), 10000, Vector3(1.0f, 1.0f, 1.0f));
	Light light(Vector3(-150.0f, 150.0f, -250), Vector3(1.0f, 1.0f, 1.0f));
	Light light2(Vector3(-200.0f, 200.0f, -100), Vector3(0.8f, 0.8f, 0.8f));
	K9::Color ambientLight(0.6f, 0.6f, 0.6f);
	Sphere sphere(Vector3(0.0f, 0.0f, -300.0f), 100, sMaterial1);
	Sphere sphere2(Vector3(300.0f, -30.0f, -400.0f), 100, sMaterial2);
	Plane plane(Vector3(0.0f, -130.0f, -300.0f), Vector3(0.0f, 1.0f, 0.0f), pMaterial);
	Plane plane2(Vector3(0.0f, 250.0f, -700.0f), Vector3(0.0f, -1.0f, 1.0f), pMaterial2);

	vector<Surface*> objects = { &sphere, &sphere2, &plane };
	vector<Light*> lights = {  &light2 };

	draw(renderer, objects, camera, lights, ambientLight);

	renderer.show(0, 0);

	waitKey();

	delete camera;

	return 0;
}

void draw(K9::Renderer &renderer, const std::vector<K9::Surface*> &objects, const K9::Camera *camera, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight) {
	using namespace K9;
	for (int i = 0; i < renderer.window().width; ++i) {
		for (int j = 0; j < renderer.window().height; ++j) {
			Ray ray = camera->calculateRay(i, j, renderer.window().width, renderer.window().height);
			Color color = rayColor(ray, 0, 100000, objects, lights, ambientLight, 2);
			renderer.drawPoint(Geometry::Point2D(i, renderer.window().height - j - 1), color);
		}
	}
}

K9::Color rayColor(const K9::Ray &ray, float t0, float t1, const vector<K9::Surface*> &objects, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight, int recursionDepth) {
	using namespace std;
	using namespace K9;
	Color color(0.0f, 1.0f, 0.0f);
	for (auto it = objects.begin(); it != objects.end(); it++) {
		unique_ptr<HitRecord> hr = nullptr;
		if ((*it)->hit(ray, t0, t1, hr)) {
			t1 = hr->t;
			Vector3 point = ray.origin() + hr->t * ray.direction();
			color = perElementProduct(hr->ka, ambientLight);
			for (auto lightIt = lights.begin(); lightIt != lights.end(); lightIt++) {
				if (!isShadowed(point, 1.0f, 500, objects, *lightIt)) {
					Vector3 l(normalized((*lightIt)->position() - point));
					Vector3 h(normalized(l + normalized(-ray.direction())));
					color = color + perElementProduct(hr->kd, (*lightIt)->intensity()) * std::max(0.0f, hr->n * l) +
						perElementProduct(hr->ks, (*lightIt)->intensity()) * powf(std::max(0.0f, hr->n*h), hr->p);
				}

				if (recursionDepth > 0 && !hr->km.isZero()) {
					Vector3 mirrorReflectionDirection = getMirrorReflectionDirection(ray.direction(), hr->n);
					color = color + perElementProduct(hr->km, rayColor(Ray(point, mirrorReflectionDirection), 0.5f, 1000, objects, lights, ambientLight, recursionDepth - 1));
				}
			}
		}
	}

	return Color(std::min(1.0f, color[0]), std::min(1.0f, color[1]), std::min(1.0f, color[2]));
}

bool isShadowed(const K9::Vector3 &origin, float t0, float t1, const vector<K9::Surface*> &objects, const K9::Light *light) {
	using namespace std;
	using namespace K9;
	bool hit = false;
	Ray ray(origin, normalized(light->position() - origin));
	for (auto oIt = objects.begin(); oIt != objects.end(); oIt++) {
		unique_ptr<HitRecord> hr = nullptr;
		if ((*oIt)->hit(ray, t0, t1, hr)) {
			hit = true;
			break;
		}
	}

	return hit;
}

inline K9::Vector3 getMirrorReflectionDirection(const K9::Vector3 &viewDirection, const K9::Vector3 &surfaceNormal) {
	using namespace K9;

	return normalized( viewDirection - 2*(viewDirection*surfaceNormal)*surfaceNormal);
}