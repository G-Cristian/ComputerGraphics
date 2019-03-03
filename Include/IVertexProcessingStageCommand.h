#ifndef _IVERTEXPROCESSINGSTAGECOMMAND_H_
#define _IVERTEXPROCESSINGSTAGECOMMAND_H_

#include <memory>
#include <Vertex.h>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline;
		class IVertexProcessingStageCommand {
		public:
			virtual ~IVertexProcessingStageCommand() = default;
			virtual Vertex execute(Vertex &, std::weak_ptr<GraphicsPipeline> ) = 0;
		protected:
			IVertexProcessingStageCommand() = default;
		};
	}
}

#endif // !_IVERTEXPROCESSINGSTAGECOMMAND_H_