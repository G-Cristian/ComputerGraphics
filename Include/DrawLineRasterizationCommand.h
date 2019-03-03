#ifndef _DRAWLINERASTERIZATIONCOMMAND_H_
#define _DRAWLINERASTERIZATIONCOMMAND_H_

#include <IRasterizationCommand.h>

namespace K9 {
	namespace GraphicsPipeline {
		class RasterizationStage;
		class DrawLineRasterizationCommand :public IRasterizationCommand {
		public:
			DrawLineRasterizationCommand(int p1, int p2, int baseIndex) :
				IRasterizationCommand(baseIndex),
				_p1(p1),
				_p2(p2) {
			}

			virtual ~DrawLineRasterizationCommand() {}
			void execute(const RasterizationStage&, std::vector<FragmentProcessingStageParameters::Fragment>&) const override final;
		private:
			DrawLineRasterizationCommand(const DrawLineRasterizationCommand &) = delete;
			DrawLineRasterizationCommand& operator=(const DrawLineRasterizationCommand &) = delete;
			DrawLineRasterizationCommand(DrawLineRasterizationCommand &&)noexcept = delete;
			DrawLineRasterizationCommand& operator=(DrawLineRasterizationCommand &&)noexcept = delete;

			int _p1;
			int _p2;
		};
	}
}

#endif // !_DRAWLINERASTERIZATIONCOMMAND_H_
