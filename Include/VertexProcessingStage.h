#ifndef _VERTEXPROCESSINGSTAGE_H_
#define _VERTEXPROCESSINGSTAGE_H_

#include <IGraphicsPipelineStage.h>
#include <memory>
#include <RasterizationStage.h>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline;
		class VertexProcessingStage : public IGraphicsPipelineStage {
		public:
			VertexProcessingStage() :
				IGraphicsPipelineStage() {
			}
			virtual ~VertexProcessingStage() = default;
			void execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) override final;
			void setNextStage(std::weak_ptr<GraphicsPipeline> graphicsPipeline, const GraphicsPipelineStageParametersProxy &parameters) const override final {
				IGraphicsPipelineStage::setNextStage(graphicsPipeline, std::make_shared<RasterizationStage>(parameters));
			}
		private:
			VertexProcessingStage(const IGraphicsPipelineStage &other) = delete;
			VertexProcessingStage& operator=(const IGraphicsPipelineStage &other) = delete;
			VertexProcessingStage(IGraphicsPipelineStage &&other) noexcept = delete;
			VertexProcessingStage& operator=(IGraphicsPipelineStage &&other) noexcept = delete;
		};
	}
}

#endif // !_VERTEXPROCESSINGSTAGE_H_
