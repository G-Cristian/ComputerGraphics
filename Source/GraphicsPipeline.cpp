#include <GraphicsPipeline.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		std::shared_ptr<GraphicsPipeline> GraphicsPipeline::_instance = nullptr;
		
		void GraphicsPipeline::execute() {
			while (_currentStage != nullptr) {
				_currentStage->execute(GraphicsPipeline::_instance);
				_currentStage->setNextStage(GraphicsPipeline::_instance, _currentStage->getOutParameters());
			}
		}

	}
}