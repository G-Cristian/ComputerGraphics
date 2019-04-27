#include <GraphicsPipeline.h>
#include <memory>

namespace K9 {
	namespace GraphicsPipeline {
		std::shared_ptr<GraphicsPipeline> GraphicsPipeline::_instance = nullptr;
		
		void GraphicsPipeline::setBuffersSize(int width, int height) {
			_frontBuffer = std::make_shared<Image>(width, height);
			_backBuffer = std::make_shared<Image>(width, height);
			_width = width;
			_height = height;
		}

		void GraphicsPipeline::clearBackBuffer(Color32 color) {
			//TODO: implement a clear image method in image and use it
			unsigned int width = _backBuffer->getWidth();
			unsigned int height = _backBuffer->getHeight();
			for (unsigned int i = 0; i < height; ++i) {
				for (unsigned int j = 0; j < width; ++j) {
					_backBuffer->setColorAtXY(color, j, i);
				}
			}
		}

		void GraphicsPipeline::setColorToBackBuffer(int x, int y, Color32 color) {
			_backBuffer->setColorAtXY(color, x, y);
		}

		void GraphicsPipeline::execute() {
			while (_currentStage != nullptr) {
				_currentStage->execute(GraphicsPipeline::_instance);
				_currentStage->setNextStage(GraphicsPipeline::_instance, _currentStage->getOutParameters());
			}
		}

	}
}