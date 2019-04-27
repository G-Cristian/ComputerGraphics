#ifndef _GRAPHICSPIPELINESTAGEPARAMETERSPROXY_H_
#define _GRAPHICSPIPELINESTAGEPARAMETERSPROXY_H_

#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class IGraphicsPipelineStage;
		class IGraphicsPipelineStageParameters;
		class VertexProcessingStageParameters;
		class RasterizationStageParameters;
		class FragmentProcessingStageParameters;
		class BlendingStageParameters;
	}
}

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipelineStageParametersProxy {
		public:
			GraphicsPipelineStageParametersProxy(const std::shared_ptr<IGraphicsPipelineStageParameters> &parameters):
				_parameters(parameters){
			}

			~GraphicsPipelineStageParametersProxy() = default;

			GraphicsPipelineStageParametersProxy(const GraphicsPipelineStageParametersProxy &other) :
				_parameters(other._parameters) {
			}

			//add getters for each concrete GraphicsPipelineStageParameters

			VertexProcessingStageParameters* getVertexProcessingStageParameters() const;
			RasterizationStageParameters* getRasterizationStageParameters() const;
			FragmentProcessingStageParameters* getFragmentProcessingStageParameters() const;
			BlendingStageParameters* getBlendingStageParameters() const;

		private:
			std::shared_ptr<IGraphicsPipelineStageParameters> _parameters;
		};
	}
}

#endif // !_GRAPHICSPIPELINESTAGEPARAMETERSPROXY_H_
