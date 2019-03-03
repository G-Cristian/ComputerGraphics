#include <GraphicsPipeline.h>
#include <memory>
#include <RasterizationStageParameters.h>
#include <vector>
#include <VertexProcessingStage.h>

namespace K9 {
	namespace GraphicsPipeline {
		void VertexProcessingStage::execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) {
			std::shared_ptr<GraphicsPipeline> gp = graphicsPipeline.lock();
			RasterizationStageParameters *rasterizationStageParameters = new RasterizationStageParameters();
			std::vector<Vertex> &outVertex = rasterizationStageParameters->vertexes();
			if (gp != nullptr) {
				GraphicsPipeline::VertexesType &vertexes = gp->getVertexes();
				outVertex.reserve(vertexes.size());
				for (auto it = vertexes.begin(); it != vertexes.end(); ++it) {
					outVertex.push_back(gp->vertexProcessingStageCommand()->execute(*it, gp));
				}
			}
			
			_outParameters = GraphicsPipelineStageParametersProxy(std::shared_ptr<RasterizationStageParameters>(rasterizationStageParameters));
		}
	}
}