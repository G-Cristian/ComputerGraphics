#include <DrawTriangleRasterizationCommand.h>
#include <RasterizationStage.h>

namespace K9 {
	namespace GraphicsPipeline {
		void DrawTriangleRasterizationCommand::execute(const RasterizationStage &rasterizationStage, std::vector<FragmentProcessingStageParameters::Fragment>& outFragments) const {
			rasterizationStage.drawTriangleIntoFragments(_p1 + _baseIndex, _p2 + _baseIndex, _p3 + _baseIndex, outFragments);
		}
	}
}