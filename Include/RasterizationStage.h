#ifndef _RASTERIZATIONSTAGE_H_
#define _RASTERIZATIONSTAGE_H_

#include <FragmentProcessingStage.h>
#include <FragmentProcessingStageParameters.h>
#include <IGraphicsPipelineStage.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline;
		class RasterizationStage : public IGraphicsPipelineStage {
		public:
			RasterizationStage(const GraphicsPipelineStageParametersProxy &parameters) :
				IGraphicsPipelineStage(parameters) {
			}
			virtual ~RasterizationStage() = default;
			void execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) override final;
			void setNextStage(std::weak_ptr<GraphicsPipeline> graphicsPipeline, const GraphicsPipelineStageParametersProxy &parameters) const override final {
				IGraphicsPipelineStage::setNextStage(graphicsPipeline, std::make_shared<FragmentProcessingStage>(parameters));
			}

			void drawLineIntoFragments(int p1, int p2, std::vector<FragmentProcessingStageParameters::Fragment> &) const;
			void drawTriangleIntoFragments(int p1, int p2, int p3, std::vector<FragmentProcessingStageParameters::Fragment> &) const;

		private:
			RasterizationStage(const IGraphicsPipelineStage &other) = delete;
			RasterizationStage& operator=(const IGraphicsPipelineStage &other) = delete;
			RasterizationStage(IGraphicsPipelineStage &&other) noexcept = delete;
			RasterizationStage& operator=(IGraphicsPipelineStage &&other) noexcept = delete;
		};
	}
}

#endif // !_RASTERIZATIONSTAGE_H_