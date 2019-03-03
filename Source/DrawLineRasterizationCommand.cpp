#include <DrawLineRasterizationCommand.h>
#include <RasterizationStage.h>

namespace K9 {
	namespace GraphicsPipeline {
		void DrawLineRasterizationCommand::execute(const RasterizationStage &rasterizationStage, std::vector<FragmentProcessingStageParameters::Fragment>& outFragments) const {
			rasterizationStage.drawLineIntoFragments(_p1 + _baseIndex, _p2 + _baseIndex, outFragments);
		}
	}
}