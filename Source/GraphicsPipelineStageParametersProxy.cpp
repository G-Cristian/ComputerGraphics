#include <assert.h>
#include <BlendingStageParameters.h>
#include <GraphicsPipelineStageParametersProxy.h>
#include <FragmentProcessingStageParameters.h>
#include <RasterizationStageParameters.h>
#include <VertexProcessingStageParameters.h>

namespace K9 {
	namespace GraphicsPipeline {
		VertexProcessingStageParameters* GraphicsPipelineStageParametersProxy::getVertexProcessingStageParameters() const {
			VertexProcessingStageParameters *parameters = dynamic_cast<VertexProcessingStageParameters*>(_parameters.get());
			assert(parameters != nullptr);
			return parameters;
		}

		RasterizationStageParameters* GraphicsPipelineStageParametersProxy::getRasterizationStageParameters() const {
			RasterizationStageParameters *parameters = dynamic_cast<RasterizationStageParameters*>(_parameters.get());
			assert(parameters != nullptr);
			return parameters;
		}

		FragmentProcessingStageParameters* GraphicsPipelineStageParametersProxy::getFragmentProcessingStageParameters() const {
			FragmentProcessingStageParameters *parameters = dynamic_cast<FragmentProcessingStageParameters*>(_parameters.get());
			assert(parameters != nullptr);
			return parameters;
		}

		BlendingStageParameters* GraphicsPipelineStageParametersProxy::getBlendingStageParameters() const {
			BlendingStageParameters *parameters = dynamic_cast<BlendingStageParameters*>(_parameters.get());
			assert(parameters != nullptr);
			return parameters;
		}
	}
}