#include <Color.h>
#include <math.h>
#include <Matrix4.h>
#include <memory>
#include <Vector4.h>
#include <VertexProcessingStageCommand.h>

namespace K9 {
	namespace GraphicsPipeline {
		Vertex VertexProcessingStageCommand::execute(Vertex &inVertex, std::weak_ptr<GraphicsPipeline> graphicsPipeline) {
			std::shared_ptr<GraphicsPipeline> gp = graphicsPipeline.lock();
			Vertex outVertex;
			if (gp != nullptr) {
				Vector4 point(*inVertex.getPropertyByName("position"));
//				Vector4 color= *inVertex.getPropertyByName("color");
//				color = perElementProduct(*inVertex.getPropertyByName("ka"), Vector4(gp->ambientLight(), 0.0f));
//				for (auto lightIt = gp->lights().begin(); lightIt != gp->lights().end(); lightIt++) {
//					Vector4 l(normalized(Vector4(lightIt->position(), 0.0f) - point));
//					Vector4 h(normalized(l + normalized(Vector4(gp->getCamera()->position(),0.0f)-point)));
//					
//					color = color + perElementProduct(*inVertex.getPropertyByName("kd"), Vector4(lightIt->intensity(),0.0f)) * std::max(0.0f, dot(*inVertex.getPropertyByName("normal"), l)) +
//						perElementProduct(*inVertex.getPropertyByName("ks"), Vector4(lightIt->intensity(),0.0f)) * powf(std::max(0.0f, dot(*inVertex.getPropertyByName("normal"), h)), (*inVertex.getPropertyByName("p"))[0]);
//					
//					//TODO: Test for faces pointing backwards
//					if (dot(Vector4(gp->getCamera()->position(), 0.0f) - point, *inVertex.getPropertyByName("normal")) < 0.0f) {
//						color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
//					}
//				}

				const Matrix4 &MCam = gp->getCameraTransformation();
				const Matrix4 &MProj = gp->getProjectionTransformation();
				const Matrix4 &MView = gp->getViewportTransformation();

				Vector4 originalPos = *inVertex.getPropertyByName("position");
				//originalPos[3] = 0.0f;
				outVertex.setPropertyByName("originalPosition", originalPos);
				outVertex.setPropertyByName("ka", *inVertex.getPropertyByName("ka"));
				outVertex.setPropertyByName("kd", *inVertex.getPropertyByName("kd"));
				outVertex.setPropertyByName("ks", *inVertex.getPropertyByName("ks"));
				outVertex.setPropertyByName("p", *inVertex.getPropertyByName("p"));
				outVertex.setPropertyByName("position", MView*MProj*MCam*(*inVertex.getPropertyByName("position")));
//				outVertex.setPropertyByName("color", Vector4(std::min(1.0f, color[0]), std::min(1.0f, color[1]), std::min(1.0f, color[2]), std::min(1.0f, color[3])));
				outVertex.setPropertyByName("normal", *inVertex.getPropertyByName("normal"));
			}

			return outVertex;
		}
	}
}