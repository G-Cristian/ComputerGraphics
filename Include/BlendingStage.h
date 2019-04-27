#ifndef _BLENDINGSTAGE_H_
#define _BLENDINGSTAGE_H_

#include <IGraphicsPipelineStage.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline;
		class BlendingStage : public IGraphicsPipelineStage {
		public:
			BlendingStage(const GraphicsPipelineStageParametersProxy &parameters) :
				IGraphicsPipelineStage(parameters) {
			}
			virtual ~BlendingStage() = default;
			void execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) override final;
			void setNextStage(std::weak_ptr<GraphicsPipeline> graphicsPipeline, const GraphicsPipelineStageParametersProxy &parameters) const override final {
				IGraphicsPipelineStage::setNextStage(graphicsPipeline, nullptr);
			}
		private:
			BlendingStage(const IGraphicsPipelineStage &other) = delete;
			BlendingStage& operator=(const IGraphicsPipelineStage &other) = delete;
			BlendingStage(IGraphicsPipelineStage &&other) noexcept = delete;
			BlendingStage& operator=(IGraphicsPipelineStage &&other) noexcept = delete;
		};
	}
}


#endif // !_BLENDINGSTAGE_H_
