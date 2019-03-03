#ifndef _DRAWTRIANGLERASTERIZATIONCOMMAND_H_
#define _DRAWTRIANGLERASTERIZATIONCOMMAND_H_

#include <IRasterizationCommand.h>

namespace K9 {
	namespace GraphicsPipeline {
		class RasterizationStage;
		class DrawTriangleRasterizationCommand:public IRasterizationCommand {
		public:
			DrawTriangleRasterizationCommand(int p1, int p2, int p3, int baseIndex) :
				IRasterizationCommand(baseIndex),
				_p1(p1),
				_p2(p2),
				_p3(p3) {
			}

			virtual ~DrawTriangleRasterizationCommand() {}
			void execute(const RasterizationStage&, std::vector<FragmentProcessingStageParameters::Fragment>&) const override final;
		private:
			DrawTriangleRasterizationCommand(const DrawTriangleRasterizationCommand &) = delete;
			DrawTriangleRasterizationCommand& operator=(const DrawTriangleRasterizationCommand &) = delete;
			DrawTriangleRasterizationCommand(DrawTriangleRasterizationCommand &&)noexcept = delete;
			DrawTriangleRasterizationCommand& operator=(DrawTriangleRasterizationCommand &&)noexcept = delete;

			int _p1;
			int _p2;
			int _p3;
		};
	}
}

#endif // !_DRAWTRIANGLERASTERIZATIONCOMMAND_H_
