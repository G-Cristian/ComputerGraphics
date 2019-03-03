#ifndef _FRAGMENTPROCESSINGSTAGE_H_
#define _FRAGMENTPROCESSINGSTAGE_H_

#include <IGraphicsPipelineStage.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline;
		class FragmentProcessingStage : public IGraphicsPipelineStage {
		public:
			FragmentProcessingStage(const GraphicsPipelineStageParametersProxy &parameters) :
				IGraphicsPipelineStage(parameters) {
			}
			virtual ~FragmentProcessingStage() = default;
			void execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) override final;
			void setNextStage(std::weak_ptr<GraphicsPipeline> graphicsPipeline, const GraphicsPipelineStageParametersProxy &parameters) const override final {
				IGraphicsPipelineStage::setNextStage(graphicsPipeline, nullptr);
			}
		private:
			FragmentProcessingStage(const IGraphicsPipelineStage &other) = delete;
			FragmentProcessingStage& operator=(const IGraphicsPipelineStage &other) = delete;
			FragmentProcessingStage(IGraphicsPipelineStage &&other) noexcept = delete;
			FragmentProcessingStage& operator=(IGraphicsPipelineStage &&other) noexcept = delete;
		};
	}
}

#endif // !_FRAGMENTPROCESSINGSTAGE_H_
