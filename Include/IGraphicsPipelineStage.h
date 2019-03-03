#ifndef _IGRAPHICSPIPELINESTAGE_H_
#define _IGRAPHICSPIPELINESTAGE_H_

#include <GraphicsPipelineStageParametersProxy.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline;
	}
}

namespace K9 {
	namespace GraphicsPipeline {
		class IGraphicsPipelineStageParameters {
		public:
			virtual ~IGraphicsPipelineStageParameters() = default;
		protected:
			IGraphicsPipelineStageParameters() = default;
			IGraphicsPipelineStageParameters(const IGraphicsPipelineStageParameters &other) = default;
			IGraphicsPipelineStageParameters& operator=(const IGraphicsPipelineStageParameters &other) = default;
		};

		class IGraphicsPipelineStage {
		public:
			virtual ~IGraphicsPipelineStage() = default;
			virtual void execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) = 0;
			virtual void setNextStage(std::weak_ptr<GraphicsPipeline> graphicsPipeline, const GraphicsPipelineStageParametersProxy &parameters) const = 0;
			
			const GraphicsPipelineStageParametersProxy& getParameters() const {
				return _parameters;
			}

			GraphicsPipelineStageParametersProxy& getParameters() {
				return _parameters;
			}

			void setParameters(const GraphicsPipelineStageParametersProxy &parameters) {
				_parameters = parameters;
			}

			const GraphicsPipelineStageParametersProxy& getOutParameters() const {
				return _outParameters;
			}

			GraphicsPipelineStageParametersProxy& getOutParameters() {
				return _outParameters;
			}

			void setOutParameters(const GraphicsPipelineStageParametersProxy &parameters) {
				_outParameters = parameters;
			}

		protected:
			IGraphicsPipelineStage() :
				_parameters(nullptr),
				_outParameters(nullptr){
			}

			IGraphicsPipelineStage(const GraphicsPipelineStageParametersProxy &parameters) :
				_parameters(parameters),
				_outParameters(nullptr){
			}

			IGraphicsPipelineStage(const IGraphicsPipelineStage &other) :
				_parameters(other._parameters),
				_outParameters(other._outParameters){
			}

			IGraphicsPipelineStage& operator=(const IGraphicsPipelineStage &other) {
				_parameters = other._parameters;
				_outParameters = other._outParameters;
			}

			void setNextStage(std::weak_ptr<GraphicsPipeline> &graphicsPipeline, const std::shared_ptr<IGraphicsPipelineStage> &nextStage) const;

			GraphicsPipelineStageParametersProxy _parameters;
			GraphicsPipelineStageParametersProxy _outParameters;
		};
	}
}

#endif // !_IGRAPHICSPIPELINESTAGE_H_
