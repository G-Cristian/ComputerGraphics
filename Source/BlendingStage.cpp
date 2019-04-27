#include <BlendingStage.h>
#include <GaussianFilter.h>
#include <GraphicsPipeline.h>
#include <ImageOperations.h>
#include <memory>
#include <renderer.h>
#include <Vector3.h>
#include <Vector4.h>

namespace K9 {
	namespace GraphicsPipeline {
		void BlendingStage::execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) {
			std::shared_ptr<GraphicsPipeline> gp = graphicsPipeline.lock();

			if (gp != nullptr) {
				std::shared_ptr<Renderer> renderer = gp->getRenderer();
				std::shared_ptr<const Image> bb = gp->getBackBuffer();
				GaussianFilter filter(1.0f, 3.0f);
				Images::ImageOperations imgOp;
				Image im(1,1);
				if (gp->getMultisampleLevel() != 1) {
					im = imgOp.resample(*bb, (float)gp->width() / (float)gp->getMultisampleLevel(), (float)gp->height() / (float)gp->getMultisampleLevel(), filter);
				}
				else {
					im = *bb;
				}
				int width = im.getWidth();
				int height = im.getHeight();
				for (int y = 0; y < height; ++y) {
					for (int x = 0; x < width; ++x) {
						Color32 c = im.getColorAtXY(x, y);
						::K9::Color color(getRedColor32(c), getGreenColor32(c), getBlueColor32(c));
						renderer->drawPoint(Geometry::Point2D(x, y), color);
					}
				}
				gp->swapBuffers();
			}
		}
	}
}