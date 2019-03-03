#ifndef _VERTEXPROCESSINGSTAGECOMMAND_H_
#define _VERTEXPROCESSINGSTAGECOMMAND_H_

#include <Vertex.h>
#include <IVertexProcessingStageCommand.h>

#include <GraphicsPipeline.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline{
		class VertexProcessingStageCommand:public IVertexProcessingStageCommand {
		public:
			VertexProcessingStageCommand() :
				IVertexProcessingStageCommand() {
			}
			virtual ~VertexProcessingStageCommand() {}
			Vertex execute(Vertex &, std::weak_ptr<GraphicsPipeline>) override final;
		};
	}
}

#endif // !_VERTEXPROCESSINGSTAGECOMMAND_H_
