#include "ForwardRenderer.h"
#include "BF/Engine.h"
#include "BF/Math/Vector3.h"
#include "BF/Math/Matrix4.h"
#include "BF/ECS/GameObject.h"
#include "BF/Graphics/Transform.h"

namespace BF
{
	namespace Graphics
	{
		namespace Renderers
		{
			using namespace BF::Graphics::Materials;
			using namespace BF::Graphics::API;
			using namespace BF::Math;

			ForwardRenderer::ForwardRenderer(Camera& camera) : 
				camera(camera)
			{

			}

			ForwardRenderer::~ForwardRenderer()
			{
			}

			void ForwardRenderer::Initialize()
			{
				materialConstantBuffer.Create(sizeof(MeshMaterial::ColorBuffer), 2);
				camera.Initialize(Matrix4::Perspective(45.0f, BF::Engine::GetWindow().GetAspectRatio(), 0.1f, 1500.0f));

				/*postProcessingTexture.Create(Texture::TextureData(Engine::GetWindow().GetClientWidth(), Engine::GetWindow().GetClientHeight(), nullptr), Texture::Format::R8G8B8A8);
				postProcessingFramebuffer.Create(postProcessingTexture, FramebufferFormat::Color);
				postProcessingShader.LoadStandardShader(ShaderType::ShadowMapShader);

				postProcessingQuad = new Mesh(Mesh::PresetMeshes::Plane);
				screenPlaneMaterial = new MeshMaterial();

				screenPlaneMaterial->Initialize();
				screenPlaneMaterial->shader = &postProcessingShader;
				postProcessingQuad->SetBuffers(screenPlaneMaterial);*/
			}

			void ForwardRenderer::Render()
			{
				//postProcessingFramebuffer.Bind();
				BF::Engine::GetContext().Clear(BufferClearType::ColorAndDepth, Color(0.5, 0.0f, 0.0f, 1.0f));
				BF::Engine::GetContext().EnableDepthBuffer(true);

				for (size_t i = 0; i < meshes.size(); i++)
				{
					Transform* transform = (Transform*)meshes[i]->gameObject->GetComponents()[0];
					camera.SetModelMatrix(Matrix4::Translate(transform->position) * Matrix4::Rotate(transform->angle, transform->rotation) * Matrix4::Scale(transform->scale));

					materialConstantBuffer.Update(&meshes[i]->material->colorBuffer, sizeof(MeshMaterial::ColorBuffer));

					meshes[i]->material->Bind();
					meshes[i]->Bind();
					Engine::GetContext().Draw((unsigned int)meshes[i]->GetIndices()->size());
					meshes[i]->Unbind();
					meshes[i]->material->Unbind();
				}

				/*postProcessingFramebuffer.Unbind();


				BF::Engine::GetContext().Clear(BufferClearType::Color, Color(0.5, 0.5f, 0.5f, 1.0f));
				BF::Engine::GetContext().EnableDepthBuffer(false);

				postProcessingShader.Bind();
				postProcessingQuad->Bind();
				postProcessingTexture.Bind(postProcessingShader, "screenTexture", 0);
				Engine::GetContext().Draw((unsigned int)postProcessingQuad->GetIndices()->size());
				postProcessingTexture.Unbind();
				postProcessingQuad->Unbind();
				postProcessingShader.Unbind();*/

				BF::Engine::GetContext().SwapBuffers();
			}
		}
	}
}