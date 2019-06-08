#define _USE_MATH_DEFINES

#include <algorithm>
#include <Camera.h>
#include <Light.h>
#include <math.h>
#include <memory>
#include <PerspectiveCamera.h>
#include <Plane.h>
#include <Point2D.h>
#include <random>
#include <Ray.h>
#include <renderer.h>
#include <SolidMaterialColor.h>
#include <Sphere.h>
#include <string>
#include <Surface.h>
#include <TextureMaterialColor.h>
#include <vector>
#include <Vector4.h>

void draw(K9::Renderer &renderer, const std::vector<K9::Surface*> &objects, const K9::Camera *camera, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight);
K9::Color rayColor(const K9::Ray &ray, float t0, float t1, const vector<K9::Surface*> &objects, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight, int recursionDepth, const std::pair<float,float> &s);
bool isShadowed(const K9::Vector4 &origin, float t0, float t1, const vector<K9::Surface*> &objects, const K9::Light *light, const std::pair<float, float> &sp);
inline K9::Vector4 getMirrorReflectionDirection(const K9::Vector4 &viewDirection, const K9::Vector4 &surfaceNormal);

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
	Material sMaterial1(SolidMaterialColor(0.5f, 0.0f, 0.0f,1.0f), SolidMaterialColor(1.0f, 0.0f, 0.0f, 1.0f), SolidMaterialColor(0.8f, 0.8f, 0.8f, 1.0f), 70, SolidMaterialColor(0.0f, 0.0f, 0.0f, 1.0f));
	Material sMaterial2(SolidMaterialColor(0.5f, 0.0f, 0.0f, 1.0f), SolidMaterialColor(1.0f, 0.0f, 0.0f, 1.0f), SolidMaterialColor(0.5f, 0.5f, 0.5f, 1.0f), 100, SolidMaterialColor(0.2f, 0.2f, 0.2f, 1.0f));
	Material pMaterial(SolidMaterialColor(0.3f, 0.3f, 0.3f, 1.0f), SolidMaterialColor(0.5f, 0.5f, 0.5f, 1.0f), SolidMaterialColor(1.0f, 1.0f, 1.0f, 1.0f), 10000, SolidMaterialColor(1.0f, 1.0f, 1.0f, 1.0f));
	Material pMaterial2(SolidMaterialColor(0.8f, 0.8f, 0.8f, 1.0f), SolidMaterialColor(0.1f, 0.1f, 0.1f, 1.0f), SolidMaterialColor(1.0f, 1.0f, 1.0f, 1.0f), 10000, SolidMaterialColor(1.0f, 1.0f, 1.0f, 1.0f));
	Light light(Vector3(-150.0f, 150.0f, -250), Vector3(1.0f, 1.0f, 1.0f));
	Light light2(Vector3(-200.0f, 200.0f, -100), Vector3(0.8f, 0.8f, 0.8f));
	K9::Color ambientLight(0.6f, 0.6f, 0.6f, 1.0f);
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
	int n = 4;
	int n2 = n*n;
	float fn = n;
	float fn2 = n2;

	std::default_random_engine generator;
	std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

	for (int i = 0; i < renderer.window().width; ++i) {
		float fi = (float)(i);
		for (int j = 0; j < renderer.window().height; ++j) {
			float fj = (float)(j);
			Color color(0.0f,0.0f,0.0f,0.0f);

			std::vector<std::pair<float, float>> r;
			r.reserve(n2);
			for (int p = 0; p < n; p++) {
				for (int q = 0; q < n; q++) {
					float ep = distribution(generator);
					std::pair<float, float> tmp = { ((float)(p)+ep) / fn , ((float)(q)+ep) / fn };
					r.push_back(tmp);
				}
			}
			std::vector<std::pair<float, float>> s;
			s.reserve(n2);
			for (int p = 0; p < n; p++) {
				for (int q = 0; q < n; q++) {
					float ep = distribution(generator);
					std::pair<float, float> tmp = { ((float)(p) - fn/2.0f + 0.5f + ep) * 30.0f / fn , ((float)(q) - fn/2.0f + 0.5f + ep) * 30.0f / fn };
					s.push_back(tmp);
				}
			}

			std::shuffle(std::begin(s), std::end(s), generator);
			for (int p = 0; p < n2; ++p) {
				Ray ray = camera->calculateRay(fi + r[p].first, fj + r[p].second, renderer.window().width, renderer.window().height);
				color += rayColor(ray, 0, 100000, objects, lights, ambientLight, 2, s[p]);
			}
			color = color / fn2;
			renderer.drawPoint(Geometry::Point2D(i, renderer.window().height - j - 1), color*255);
		}
	}
}

K9::Color rayColor(const K9::Ray &ray, float t0, float t1, const vector<K9::Surface*> &objects, const std::vector<K9::Light*> &lights, const K9::Color &ambientLight, int recursionDepth, const std::pair<float, float> &s) {
	using namespace std;
	using namespace K9;
	Color color(0.0f, 1.0f, 0.0f);
	for (auto it = objects.begin(); it != objects.end(); it++) {
		unique_ptr<HitRecord> hr = nullptr;
		if ((*it)->hit(ray, t0, t1, hr)) {
			t1 = hr->t;
			Vector4 point = ray.origin() + hr->t * ray.direction();
			color = perElementProduct(hr->ka->colorAt(point[0], point[1]), ambientLight);

			for (auto lightIt = lights.begin(); lightIt != lights.end(); lightIt++) {
				if (!isShadowed(point, 1.0f, 500, objects, *lightIt, s)) {
					Vector4 l(normalized((*lightIt)->position() - point));
					Vector4 h(normalized(l + normalized(-ray.direction())));
					color = color + perElementProduct(hr->kd->colorAt(point[0], point[1]), (*lightIt)->intensity()) * std::max(0.0f, dot(hr->n, l)) +
						perElementProduct(hr->ks->colorAt(point[0], point[1]), (*lightIt)->intensity()) * powf(std::max(0.0f, dot(hr->n, h)), hr->p);
				}

				if (recursionDepth > 0 && !hr->km->colorAt(point[0], point[1]).isZero()) {
					Vector4 mirrorReflectionDirection = getMirrorReflectionDirection(ray.direction(), hr->n);
					color = color + perElementProduct(hr->km->colorAt(point[0], point[1]), rayColor(Ray(point, mirrorReflectionDirection), 0.5f, 1000, objects, lights, ambientLight, recursionDepth - 1, s));
				}
			}
		}
	}

	return Color(std::min(1.0f, color[0]), std::min(1.0f, color[1]), std::min(1.0f, color[2]));
}

bool isShadowed(const K9::Vector4 &origin, float t0, float t1, const vector<K9::Surface*> &objects, const K9::Light *light, const std::pair<float, float> &sp) {
	using namespace std;
	using namespace K9;
	bool hit = false;

	auto dir = light->position() - origin;
	Vector3 dirX;
	Vector3 dirY;
	if (dir[2] != 0.0f) {
		Vector3 aux1(dir[0], dir[1], dir[2]);
		Vector3 aux2 = aux1 - Vector3(5.0f, 5.0f, 0.0f);
		dirX = normalized(cross(aux1, aux2));
		dirY = normalized(cross(aux1, dirX));
	}
	else if (dir[1] != 0.0f) {
		Vector3 aux1(dir[0], dir[1], dir[2]);
		Vector3 aux2 = aux1 - Vector3(5.0f, 0.0f, 5.0f);
		dirX = normalized(cross(aux1, aux2));
		dirY = normalized(cross(aux1, dirX));
	}

	Vector4 lightPos = light->position() + Vector4(dirX*sp.first) + Vector4(dirY*sp.second);
	
	Ray ray(origin, normalized(lightPos - origin));

	for (auto oIt = objects.begin(); oIt != objects.end(); oIt++) {
		unique_ptr<HitRecord> hr = nullptr;
		if ((*oIt)->hit(ray, t0, t1, hr)) {
			hit = true;
			break;
		}
	}

	return hit;
}

inline K9::Vector4 getMirrorReflectionDirection(const K9::Vector4 &viewDirection, const K9::Vector4 &surfaceNormal) {
	using namespace K9;

	return normalized( viewDirection - 2*dot(viewDirection,surfaceNormal)*surfaceNormal);
}