#include <BlendingStageParameters.h>
#include <FragmentProcessingStage.h>
#include <GraphicsPipeline.h>
#include <Image.h>
#include <memory>
#include <Point2D.h>
#include <vector>

namespace K9 {
	namespace GraphicsPipeline {

		void FragmentProcessingStage::execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) {
			std::shared_ptr<GraphicsPipeline> gp = graphicsPipeline.lock();
			//BlendingStageParameters *blendingStageParameters = new BlendingStageParameters();
			//std::shared_ptr<Image> &outImage = blendingStageParameters->image();
			if (gp != nullptr) {
				FragmentProcessingStageParameters *parameters = _parameters.getFragmentProcessingStageParameters();
				if (parameters != nullptr) {
					float height = gp->height();
					const std::vector<FragmentProcessingStageParameters::Fragment> &fragments = parameters->fragments();
					for (auto it = fragments.begin(); it != fragments.end(); ++it) {
						Vector4 pos = it->properties.at("position");
						Vector4 originalPos = it->properties.at("originalPosition");
						float x = pos[0];
						float y = height - pos[1] - 1;
						::Geometry::Point2D point(x, y);
						//Vector4 col = it->properties.at("color");
						Vector4 col;
						col = perElementProduct(it->properties.at("ka"), Vector4(gp->ambientLight(), 0.0f));
						for (auto lightIt = gp->lights().begin(); lightIt != gp->lights().end(); lightIt++) {
							Vector4 l(normalized(Vector4(lightIt->position(), 0.0f) - originalPos));
							Vector4 h(normalized(l + normalized(Vector4(gp->getCamera()->position(), 0.0f) - originalPos)));

							col = col + perElementProduct(it->properties.at("kd"), Vector4(lightIt->intensity(), 0.0f)) * std::max(0.0f, dot(it->properties.at("normal"), l)) +
								perElementProduct(it->properties.at("ks"), Vector4(lightIt->intensity(), 0.0f)) * powf(std::max(0.0f, dot(it->properties.at("normal"), h)), (it->properties.at("p"))[0]);

							//TODO: Test for faces pointing backwards
//							if (dot(Vector4(gp->getCamera()->position(), 0.0f) - originalPos, it->properties.at("normal")) < 0.0f) {
//								col = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
//							}
						}

						float c1 = std::max(std::min(1.0f, col[0]),0.0f) * 255.0f;
						float c2 = std::max(std::min(1.0f, col[1]), 0.0f)* 255.0f;
						float c3 = std::max(std::min(1.0f, col[2]), 0.0f)* 255.0f;

						gp->setColorToBackBuffer(point.x, point.y, setColor32(c1, c2, c3, 255));

				//		outImage->setColorAtXY(setColor32(c1, c2, c3, 255), point.x, point.y);
					}
				}
			}

			//_outParameters = GraphicsPipelineStageParametersProxy(std::shared_ptr<BlendingStageParameters>(blendingStageParameters));
		}
	}
}