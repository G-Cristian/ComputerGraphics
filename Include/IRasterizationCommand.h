#ifndef _IRASTERIZATIONCOMMAND_H_
#define _IRASTERIZATIONCOMMAND_H_

#include <FragmentProcessingStageParameters.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		class RasterizationStage;
		class IRasterizationCommand {
		public:
			virtual ~IRasterizationCommand() = default;
			virtual void execute(const RasterizationStage&, std::vector<FragmentProcessingStageParameters::Fragment>&) const = 0;
		protected:
			IRasterizationCommand(int baseIndex) :
				_baseIndex(baseIndex) {
			}
			IRasterizationCommand(const IRasterizationCommand &) = delete;
			IRasterizationCommand& operator=(const IRasterizationCommand &) = delete;
			IRasterizationCommand(IRasterizationCommand &&)noexcept = delete;
			IRasterizationCommand& operator=(IRasterizationCommand &&)noexcept = delete;

			int _baseIndex;
		};
	}
}

#endif // !_IRASTERIZATIONCOMMAND_H_
