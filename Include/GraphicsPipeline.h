#ifndef _GRAPHICSPIPELINE_H_
#define _GRAPHICSPIPELINE_H_

//my includes
#include <Camera.h>
#include <IGraphicsPipelineStage.h>
#include <IRasterizationCommand.h>
#include <IVertexProcessingStageCommand.h>
#include <Light.h>
#include <Matrix4.h>
#include <renderer.h>
#include <Vector4.h>
#include <Vertex.h>
#include <VertexProcessingStage.h>
#include <VertexProcessingStageParameters.h>
//other includes
#include <list>
#include <memory>
#include <vector>

namespace K9 {
	namespace GraphicsPipeline {
		class GraphicsPipeline{
		public:
			typedef std::vector<Vertex> VertexesType;

			~GraphicsPipeline() = default;

			static std::weak_ptr<GraphicsPipeline> getInstance() {
				if (_instance == nullptr) {
					_instance = std::shared_ptr<GraphicsPipeline>(new GraphicsPipeline());
				}

				return std::weak_ptr<GraphicsPipeline>(_instance);
			}

			static void dispose() {
				_instance = nullptr;
			}

			//getters/setters

			const std::shared_ptr<Renderer> &getRenderer() const {
				return _renderer;
			}

			std::shared_ptr<Renderer> getRenderer() {
				return _renderer;
			}

			void setRenderer(std::shared_ptr<Renderer> renderer){
				_renderer = renderer;
			}

			const std::vector<Light>& lights() const {
				return _lights;
			}

			std::vector<Light>& lights() {
				return _lights;
			}

			const Color& ambientLight() const {
				return _ambientLight;
			}

			Color& ambientLight() {
				return _ambientLight;
			}

			//get modelingTransformation
			const Matrix4& getModelingTransformation() const {
				return _modelingTransformation;
			}
			//set modelingTransformation
			void setModelingTransformation(const Matrix4 &modelingTransformation) {
				_modelingTransformation = modelingTransformation;
			}

			//get cameraTransformation
			const Matrix4& getCameraTransformation() const{
				return _cameraTransformation;
			}
			//set cameraTransformation
			void setCameraTransformation(const Matrix4 &cameraTransformation) {
				_cameraTransformation = cameraTransformation;
			}

			//get projectionTransformation
			const Matrix4& getProjectionTransformation() const {
				return _projectionTransformation;
			}
			//set projectionTransformation
			void setProjectionTransformation(const Matrix4 &projectionTransformation) {
				_projectionTransformation = projectionTransformation;
			}

			//get viewportTransformation
			const Matrix4& getViewportTransformation() const{
				return _viewportTransformation;
			}
			//set viewportTransformation
			void setViewportTransformation(const Matrix4 &viewportTransformation) {
				_viewportTransformation = viewportTransformation;
			}

			//get vertexes
			const VertexesType& getVertexes() const {
				return _vertexes;
			}
			VertexesType& getVertexes() {
				return _vertexes;
			}
			//set vertexes
			void setVertexes(const VertexesType &vertexes) {
				_vertexes = vertexes;
			}

			Camera const *const getCamera() const {
				return _camera;
			}

			void setCamera(Camera *camera) {
				_camera = camera;
			}

			const std::shared_ptr<IVertexProcessingStageCommand>& vertexProcessingStageCommand() const { return _vertexProcessingStageCommand; }
			std::shared_ptr<IVertexProcessingStageCommand>& vertexProcessingStageCommand() { return _vertexProcessingStageCommand; }

			const std::vector<std::shared_ptr<IRasterizationCommand> >& rasterizationCommands() const { return _rasterizationCommands; }
			std::vector<std::shared_ptr<IRasterizationCommand> >& rasterizationCommands() { return _rasterizationCommands; }

			void execute();

			friend IGraphicsPipelineStage;
		private:
			GraphicsPipeline() {
				_currentStage = std::make_shared<VertexProcessingStage>();
				_currentStage->setParameters(GraphicsPipelineStageParametersProxy(std::make_shared<VertexProcessingStageParameters>()));
			}
			GraphicsPipeline(const GraphicsPipeline &other) = delete;
			GraphicsPipeline(GraphicsPipeline &&other) = delete;
			GraphicsPipeline& operator=(const GraphicsPipeline &other) = delete;
			GraphicsPipeline& operator=(GraphicsPipeline &&other) = delete;

			void setNextStage(const std::shared_ptr<IGraphicsPipelineStage> &nextStage) {
				_currentStage = nextStage;
			}


			static std::shared_ptr<GraphicsPipeline> _instance;

			std::shared_ptr<Renderer> _renderer;

			std::vector<Light> _lights;
			Color _ambientLight;

			Matrix4 _modelingTransformation;
			Matrix4 _cameraTransformation;
			Matrix4 _projectionTransformation;
			Matrix4 _viewportTransformation;
			VertexesType _vertexes;
			Camera *_camera;

			std::shared_ptr<IGraphicsPipelineStage> _currentStage;
			std::shared_ptr<IVertexProcessingStageCommand> _vertexProcessingStageCommand;
			std::vector<std::shared_ptr<IRasterizationCommand> > _rasterizationCommands;
		};
	}
}

#endif // !_GRAPHICSPIPELINE_H_
