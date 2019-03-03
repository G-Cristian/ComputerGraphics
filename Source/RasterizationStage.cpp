#include <FragmentProcessingStageParameters.h>
#include <GraphicsPipeline.h>
#include <GraphicsPipelineStageParametersProxy.h>
#include <IRasterizationCommand.h>
#include <memory>
#include <RasterizationStage.h>
#include <RasterizationStageParameters.h>
#include <vector>

#ifndef IMPLICIT_LINE_EQUATION
#define IMPLICIT_LINE_EQUATION(X0,Y0,X1,Y1,X,Y) ((Y0 - Y1)*X + (X1 - X0)*Y + X0 * Y1 - X1 * Y0)
#endif // !IMPLICIT_LINE_EQUATION

namespace K9 {
	namespace GraphicsPipeline {
		void RasterizationStage::execute(std::weak_ptr<GraphicsPipeline> graphicsPipeline) {
			std::shared_ptr<GraphicsPipeline> gp = graphicsPipeline.lock();
			FragmentProcessingStageParameters *fragmentProcesingStageParameters = new FragmentProcessingStageParameters();
			std::vector<FragmentProcessingStageParameters::Fragment> &outFragments = fragmentProcesingStageParameters->fragments();
			if (gp != nullptr) {
				std::vector<std::shared_ptr<IRasterizationCommand> > &commands = gp->rasterizationCommands();
				for (auto command = commands.begin(); command != commands.end(); ++command) {
					(*command)->execute(*this, outFragments);
				}
			}
			_outParameters = GraphicsPipelineStageParametersProxy(std::shared_ptr<FragmentProcessingStageParameters>(fragmentProcesingStageParameters));
		}

		void RasterizationStage::drawLineIntoFragments(int p1, int p2, std::vector<FragmentProcessingStageParameters::Fragment> &outFragments) const {
			using std::swap;
			RasterizationStageParameters *parameters = _parameters.getRasterizationStageParameters();
			if (parameters != nullptr) {
				//TODO: Test for faces pointing backwards
				std::shared_ptr<GraphicsPipeline> gp = GraphicsPipeline::getInstance().lock();
				if (dot(Vector4(gp->getCamera()->position(), 0.0f)- *parameters->vertexes()[p1].getPropertyByName("originalPosition"), *parameters->vertexes()[p1].getPropertyByName("normal")) < 0.0f
					|| dot(Vector4(gp->getCamera()->position(), 0.0f) - *parameters->vertexes()[p2].getPropertyByName("originalPosition"), *parameters->vertexes()[p2].getPropertyByName("normal")) < 0.0f) {
					return;
				}

				//draw line fragments into fragments
				int x0 = static_cast<int>((*parameters->vertexes()[p1].getPropertyByName("position"))[0] / (*parameters->vertexes()[p1].getPropertyByName("position"))[3]);
				float y0 = (*parameters->vertexes()[p1].getPropertyByName("position"))[1] / (*parameters->vertexes()[p1].getPropertyByName("position"))[3];
				float z0 = (*parameters->vertexes()[p1].getPropertyByName("position"))[2];
				int x1 = static_cast<int>((*parameters->vertexes()[p2].getPropertyByName("position"))[0] / (*parameters->vertexes()[p2].getPropertyByName("position"))[3]);
				float y1 = (*parameters->vertexes()[p2].getPropertyByName("position"))[1] / (*parameters->vertexes()[p2].getPropertyByName("position"))[3];
				float z1 = (*parameters->vertexes()[p2].getPropertyByName("position"))[2];
				Vector4 c0 = (*parameters->vertexes()[p1].getPropertyByName("color"));
				Vector4 c1 = (*parameters->vertexes()[p2].getPropertyByName("color"));

				Vector4 n0 = (*parameters->vertexes()[p1].getPropertyByName("normal"));
				Vector4 n1 = (*parameters->vertexes()[p2].getPropertyByName("normal"));

				Vector4 originalPos0 = (*parameters->vertexes()[p1].getPropertyByName("originalPosition"));
				Vector4 originalPos1 = (*parameters->vertexes()[p2].getPropertyByName("originalPosition"));

				if (x0 > x1) {
					swap(x0, x1);
					swap(y0, y1);
					swap(z0, z1);
					swap(c0, c1);
				}

				float m = static_cast<float>(y1 - y0) / (x1 - x0);

				if (m <= -1.0f) {
					float x = x0;
					float x1_0 = x1 - x0;
					float y0_1 = y0 - y1;
					float d = (y0_1)*(x0 + 0.5f) + (x1_0)*(y0 - 1.0f) + x0*y1 - x1*y0;
					float scale = 1.0f / (y1 - y0);
					for (int y = y0; y >= y1; --y) {
						FragmentProcessingStageParameters::Fragment fragment;
						fragment.properties["position"] = Vector4(x, y, z0 * (1 - (y - y0)*scale) + z1*(y - y0)*scale, 0.0f);
						fragment.properties["color"] = c0*(1 - (y - y0)*scale) + c1*(y - y0)*scale;
						fragment.properties["normal"] = n0*(1 - (y - y0)*scale) + n1*(y - y0)*scale;
						fragment.properties["originalPosition"] = originalPos0*(1 - (y - y0)*scale) + originalPos1*(y - y0)*scale;
						fragment.properties["ka"] = *parameters->vertexes()[p1].getPropertyByName("ka");
						fragment.properties["kd"] = *parameters->vertexes()[p1].getPropertyByName("kd");
						fragment.properties["ks"] = *parameters->vertexes()[p1].getPropertyByName("ks");
						fragment.properties["p"] = *parameters->vertexes()[p1].getPropertyByName("p");
						outFragments.push_back(fragment);
						if (d < 0.0f) {
							x = x + 1.0f;
							d = d - x1_0 + y0_1;
						}
						else {
							d = d - x1_0;
						}
					}
				}
				else if (m <= 0.0f) {
					float y = y0;
					float x1_0 = x1 - x0;
					float y0_1 = y0 - y1;
					float d = (y0_1)*(x0 + 1.0f) + (x1_0)*(y0 - 0.5f) + x0*y1 - x1*y0;
					float scale = 1.0f / (x1 - x0);
					for (int x = x0; x <= x1; ++x) {
						FragmentProcessingStageParameters::Fragment fragment;
						fragment.properties["position"] = Vector4(x, y, z0 * (1 - (x - x0)*scale) + z1*(x - x0)*scale, 0.0f);
						fragment.properties["color"] = c0*(1 - (x - x0)*scale) + c1*(x - x0)*scale;
						fragment.properties["normal"] = n0*(1 - (x - x0)*scale) + n1*(x - x0)*scale;
						fragment.properties["originalPosition"] = originalPos0*(1 - (x - x0)*scale) + originalPos1*(x - x0)*scale;
						fragment.properties["ka"] = *parameters->vertexes()[p1].getPropertyByName("ka");
						fragment.properties["kd"] = *parameters->vertexes()[p1].getPropertyByName("kd");
						fragment.properties["ks"] = *parameters->vertexes()[p1].getPropertyByName("ks");
						fragment.properties["p"] = *parameters->vertexes()[p1].getPropertyByName("p");
						outFragments.push_back(fragment);
						if (d > 0.0f) {
							y = y - 1.0f;
							d = d - x1_0 + y0_1;
						}
						else {
							d = d + y0_1;
						}
					}
				}
				else if (m <= 1.0f) {
					float y = y0;
					float x1_0 = x1 - x0;
					float y0_1 = y0 - y1;
					float d = (y0_1)*(x0 + 1.0f) + (x1_0)*(y0 + 0.5f) + x0*y1 - x1*y0;
					float scale = 1.0f / (x1 - x0);
					for (int x = x0; x <= x1; ++x) {
						FragmentProcessingStageParameters::Fragment fragment;
						fragment.properties["position"] = Vector4(x, y, z0 * (1 - (x - x0)*scale) + z1*(x - x0)*scale, 0.0f);
						fragment.properties["color"] = c0*(1 - (x - x0)*scale) + c1*(x - x0)*scale;
						fragment.properties["normal"] = n0*(1 - (x - x0)*scale) + n1*(x - x0)*scale;
						fragment.properties["originalPosition"] = originalPos0*(1 - (x - x0)*scale) + originalPos1*(x - x0)*scale;
						fragment.properties["ka"] = *parameters->vertexes()[p1].getPropertyByName("ka");
						fragment.properties["kd"] = *parameters->vertexes()[p1].getPropertyByName("kd");
						fragment.properties["ks"] = *parameters->vertexes()[p1].getPropertyByName("ks");
						fragment.properties["p"] = *parameters->vertexes()[p1].getPropertyByName("p");
						outFragments.push_back(fragment);
						if (d < 0.0f) {
							y = y + 1.0f;
							d = d + x1_0 + y0_1;
						}
						else {
							d = d + y0_1;
						}
					}
				}
				else {
					float x = x0;
					float x1_0 = x1 - x0;
					float y0_1 = y0 - y1;
					float d = (y0_1)*(x0 + 0.5f) + (x1_0)*(y0 + 1.0f) + x0*y1 - x1*y0;
					float scale = 1.0f / (y1 - y0);
					for (int y = y0; y <= y1; ++y) {
						FragmentProcessingStageParameters::Fragment fragment;
						fragment.properties["position"] = Vector4(x, y, z0 * (1 - (y - y0)*scale) + z1*(y - y0)*scale, 0.0f);
						fragment.properties["color"] = c0*(1 - (y - y0)*scale) + c1*(y - y0)*scale;
						fragment.properties["normal"] = n0*(1 - (y - y0)*scale) + n1*(y - y0)*scale;
						fragment.properties["originalPosition"] = originalPos0*(1 - (y - y0)*scale) + originalPos1*(y - y0)*scale;
						fragment.properties["ka"] = *parameters->vertexes()[p1].getPropertyByName("ka");
						fragment.properties["kd"] = *parameters->vertexes()[p1].getPropertyByName("kd");
						fragment.properties["ks"] = *parameters->vertexes()[p1].getPropertyByName("ks");
						fragment.properties["p"] = *parameters->vertexes()[p1].getPropertyByName("p");
						outFragments.push_back(fragment);
						if (d > 0.0f) {
							x = x + 1.0f;
							d = d + x1_0 + y0_1;
						}
						else {
							d = d + x1_0;
						}
					}
				}
			}
		}

		void RasterizationStage::drawTriangleIntoFragments(int p1, int p2, int p3, std::vector<FragmentProcessingStageParameters::Fragment> &outFragments) const {
			RasterizationStageParameters *parameters = _parameters.getRasterizationStageParameters();
			if (parameters != nullptr) {
				//TODO: Test for faces pointing backwards
				std::shared_ptr<GraphicsPipeline> gp = GraphicsPipeline::getInstance().lock();
				if (dot(normalized(Vector4(gp->getCamera()->position(), 1.0f) - *parameters->vertexes()[p1].getPropertyByName("originalPosition")), *parameters->vertexes()[p1].getPropertyByName("normal")) < 0.0f
					|| dot(normalized(Vector4(gp->getCamera()->position(), 1.0f) - *parameters->vertexes()[p2].getPropertyByName("originalPosition")), *parameters->vertexes()[p2].getPropertyByName("normal")) < 0.0f
					|| dot(normalized(Vector4(gp->getCamera()->position(), 1.0f) - *parameters->vertexes()[p3].getPropertyByName("originalPosition")), *parameters->vertexes()[p3].getPropertyByName("normal")) < 0.0f) {
					return;
				}

				//draw triangle into fragments
				Vector4 posV0 = (*(parameters->vertexes()[p1].getPropertyByName("position"))) / (*(parameters->vertexes()[p1].getPropertyByName("position")))[3];
				Vector4 posV1 = (*(parameters->vertexes()[p2].getPropertyByName("position"))) / (*(parameters->vertexes()[p2].getPropertyByName("position")))[3];
				Vector4 posV2 = (*(parameters->vertexes()[p3].getPropertyByName("position"))) / (*(parameters->vertexes()[p3].getPropertyByName("position")))[3];

				Vector4 c0 = (*parameters->vertexes()[p1].getPropertyByName("color"));
				Vector4 c1 = (*parameters->vertexes()[p2].getPropertyByName("color"));
				Vector4 c2 = (*parameters->vertexes()[p3].getPropertyByName("color"));

				Vector4 n0 = (*parameters->vertexes()[p1].getPropertyByName("normal"));
				Vector4 n1 = (*parameters->vertexes()[p2].getPropertyByName("normal"));
				Vector4 n2 = (*parameters->vertexes()[p3].getPropertyByName("normal"));

				Vector4 originalPos0 = (*parameters->vertexes()[p1].getPropertyByName("originalPosition"));
				Vector4 originalPos1 = (*parameters->vertexes()[p2].getPropertyByName("originalPosition"));
				Vector4 originalPos2 = (*parameters->vertexes()[p3].getPropertyByName("originalPosition"));

				unsigned int xMin = static_cast<unsigned int>(std::fminf(posV0[0], std::fminf(posV1[0], posV2[0])));
				unsigned int yMin = static_cast<unsigned int>(std::fminf(posV0[1], std::fminf(posV1[1], posV2[1])));
				//Plus 0.999... in order to aprox the ceiling
				unsigned int xMax = static_cast<unsigned int>(std::fmaxf(posV0[0], std::fmaxf(posV1[0], posV2[0])) + 0.999999f );
				unsigned int yMax = static_cast<unsigned int>(std::fmaxf(posV0[1], std::fmaxf(posV1[1], posV2[1])) + 0.999999f );

				float fAlpha = IMPLICIT_LINE_EQUATION(posV1[0], posV1[1], posV2[0], posV2[1], posV0[0], posV0[1]);
				float fBeta = IMPLICIT_LINE_EQUATION(posV2[0], posV2[1], posV0[0], posV0[1], posV1[0], posV1[1]);
				float fGamma = IMPLICIT_LINE_EQUATION(posV0[0], posV0[1], posV1[0], posV1[1], posV2[0], posV2[1]);
				float f12_1_1 = IMPLICIT_LINE_EQUATION(posV1[0], posV1[1], posV2[0], posV2[1], -1.0f, -1.0f);
				float f20_1_1 = IMPLICIT_LINE_EQUATION(posV2[0], posV2[1], posV0[0], posV0[1], -1.0f, -1.0f);
				float f01_1_1 = IMPLICIT_LINE_EQUATION(posV0[0], posV0[1], posV1[0], posV1[1], -1.0f, -1.0f);

				for (unsigned int y = yMin; y <= yMax; ++y) {
					float alpha = IMPLICIT_LINE_EQUATION(posV1[0], posV1[1], posV2[0], posV2[1], static_cast<float>(xMin), static_cast<float>(y)) / fAlpha;
					float beta = IMPLICIT_LINE_EQUATION(posV2[0], posV2[1], posV0[0], posV0[1], static_cast<float>(xMin), static_cast<float>(y)) / fBeta;
					//float gamma = IMPLICIT_LINE_EQUATION(posV0[0], posV0[1], posV1[0], posV1[1], static_cast<float>(xMin), static_cast<float>(y)) / fGamma;
					for (unsigned int x = xMin; x <= xMax; ++x) {
						//TODO: What to do if fAlpha, fBeta or fGamma are equal to 0 (degenerated triangles).
//						float alpha = IMPLICIT_LINE_EQUATION(posV1[0], posV1[1], posV2[0], posV2[1], static_cast<float>(x), static_cast<float>(y)) / fAlpha;
//						float beta = IMPLICIT_LINE_EQUATION(posV2[0], posV2[1], posV0[0], posV0[1], static_cast<float>(x), static_cast<float>(y)) / fBeta;
//						float gamma = IMPLICIT_LINE_EQUATION(posV0[0], posV0[1], posV1[0], posV1[1], static_cast<float>(x), static_cast<float>(y)) / fGamma;
						float gamma = 1.0f - alpha - beta;
						if (alpha >= 0.0f && beta >= 0.0f && gamma >= 0.0f) {
				//			std::cout << "alpha + beta + gamma = " << alpha + beta + gamma << std::endl;
							//TODO: This is test code to test if alpha + beta + gamma get greater than 1 if I calculate three values independently.
//							if (alpha + beta + gamma > 1.0f) {
	//							FragmentProcessingStageParameters::Fragment fragment;
		//						fragment.properties["position"] = Vector4(x, y, posV0[2] * alpha + posV1[2] * beta + posV2[2] * gamma, 0.0f);
			//					fragment.properties["color"] = Vector4(0.0f,1.0f,0.0f,1.0f);
				//				outFragments.push_back(fragment);
					//		}
						//	else
							{
								if ((alpha > 0.0f || fAlpha*f12_1_1 > 0) &&
									(beta > 0.0f || fBeta*f20_1_1 > 0) &&
									(gamma > 0.0f || fGamma*f01_1_1 > 0)) {

									FragmentProcessingStageParameters::Fragment fragment;
									fragment.properties["position"] = Vector4(x, y, posV0[2] * alpha + posV1[2] * beta + posV2[2] * gamma, 0.0f);
									fragment.properties["color"] = c0*alpha + c1*beta + c2*gamma;
									fragment.properties["normal"] = normalized(n0*alpha + n1*beta + n2*gamma);
									fragment.properties["originalPosition"] = originalPos0*alpha + originalPos1*beta + originalPos2*gamma;
									fragment.properties["ka"] = *parameters->vertexes()[p1].getPropertyByName("ka");
									fragment.properties["kd"] = *parameters->vertexes()[p1].getPropertyByName("kd");
									fragment.properties["ks"] = *parameters->vertexes()[p1].getPropertyByName("ks");
									fragment.properties["p"] = *parameters->vertexes()[p1].getPropertyByName("p");
							//		if ((c0*alpha + c1*beta + c2*gamma)[0] > 1.005f ) {
								//		std::cout << "alpha + beta + gamma = " << alpha + beta + gamma << std::endl;
								//		fragment.properties["color"] = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
								//	}
									outFragments.push_back(fragment);
								}
							}
						}
						alpha += (posV1[1] - posV2[1]) / fAlpha;
						beta += (posV2[1] - posV0[1]) / fBeta;
						//gamma += (posV0[1] - posV1[1]) / fGamma;
					}
				}
			}
		}
	}
}