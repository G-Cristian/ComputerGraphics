#include <GraphicsPipeline.h>
#include <IGraphicsPipelineStage.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		void IGraphicsPipelineStage::setNextStage(std::weak_ptr<GraphicsPipeline> &graphicsPipeline, const std::shared_ptr<IGraphicsPipelineStage> &nextStage) const {
			std::shared_ptr<GraphicsPipeline> gp = graphicsPipeline.lock();
			if (gp != nullptr) {
				gp->setNextStage(nextStage);
			}
		}
	}
}