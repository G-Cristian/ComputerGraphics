#ifndef _BLENDINGSTAGEPARAMETERS_H_
#define _BLENDINGSTAGEPARAMETERS_H_

#include <IGraphicsPipelineStage.h>
#include <Image.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class BlendingStageParameters : public IGraphicsPipelineStageParameters {
		public:

			BlendingStageParameters() :
				IGraphicsPipelineStageParameters() {
			}
			virtual ~BlendingStageParameters() {}

			std::shared_ptr<const Image> image() const { return _image; }
			std::shared_ptr<Image> image() { return _image; }
		private:
			std::shared_ptr<Image> _image;
		};
	}
}
#endif
