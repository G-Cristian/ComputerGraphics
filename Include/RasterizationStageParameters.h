#ifndef _RASTERIZATIONSTAGEPARAMETERS_H_
#define _RASTERIZATIONSTAGEPARAMETERS_H_

#include <IGraphicsPipelineStage.h>
#include <vector>
#include <Vertex.h>

namespace K9 {
	namespace GraphicsPipeline {
		class RasterizationStageParameters : public IGraphicsPipelineStageParameters {
		public:
			RasterizationStageParameters() :
				IGraphicsPipelineStageParameters() {
			}
			virtual ~RasterizationStageParameters() {}

			const std::vector<Vertex>& vertexes() const { return _vertexes; }
			std::vector<Vertex>& vertexes() { return _vertexes; }
		private:
			std::vector<Vertex> _vertexes;
		};
	}
}

#endif // !_RASTERIZATIONSTAGEPARAMETERS_H_
