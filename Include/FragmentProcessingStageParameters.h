#ifndef _FRAGMENTPROCESSINGSTAGEPARAMETERS_H_
#define _FRAGMENTPROCESSINGSTAGEPARAMETERS_H_

#include <Color.h>
#include <IGraphicsPipelineStage.h>
#include <map>
#include <string>
#include <vector>
#include <Vector4.h>

namespace K9 {
	namespace GraphicsPipeline {
		class FragmentProcessingStageParameters : public IGraphicsPipelineStageParameters {
		public:
			struct Fragment{
				std::map<std::string, Vector4> properties;
			};

			FragmentProcessingStageParameters():
				IGraphicsPipelineStageParameters(){
			}
			virtual ~FragmentProcessingStageParameters() {}

			const std::vector<Fragment>& fragments() const { return _fragment; }
			std::vector<Fragment>& fragments() { return _fragment; }
		private:
			std::vector<Fragment> _fragment;
		};
	}
}

#endif // !_FRAGMENTPROCESSINGSTAGEPARAMETERS_H_
