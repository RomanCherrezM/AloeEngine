#include <ECS/Systems/RenderSystem.h>

#include <ECS/Components/Components.h>

#include <Scene/SceneManager.h>
#include <Scene/Entity.h>

#include <Render/Shader.h>
#include <Render/Texture.h>
#include <Render/VertexArray.h>

#include <Core/AloeEngine.h>
#include <Core/AssetLibrary.h>

#include <glad/glad.h>

namespace Aloe
{

    // ///////////////////////////////   RenderCameraSystem /////////////////////////////// //

    RenderCameraSystem::RenderCameraSystem() 
    {

    }

    RenderCameraSystem::~RenderCameraSystem() 
    {

    }

    void RenderCameraSystem::Init() 
    {
    }

    void RenderCameraSystem::Execute()
    {
        // TODO: Move main camara to the scene itself
        CameraComponent* mainCamera = Aloe::Engine::Get()->GetMainCamera();

        if (mainCamera == nullptr) return;

        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

        for each (Entity i in scene->GetEntities<CameraComponent>())
        {
            CameraComponent& camera = i.GetComponent<CameraComponent>();

            if (camera.m_renderTarget == nullptr) continue;

            m_spriteRenderSystem->m_renderCamera = &camera;
            m_meshRenderSystem->m_renderCamera = &camera;

            // Clear
            camera.m_renderTarget->Bind();

            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glEnable(GL_DEPTH_TEST);

            // Render Scene
            m_spriteRenderSystem->Execute();
            m_meshRenderSystem->Execute();

            // End Frame buffer
            camera.m_renderTarget->Unbind();
        }

        if (mainCamera->m_renderTarget == nullptr) return;

        Renderer::Get()->DrawFullScreenQuad(mainCamera->m_renderTarget->GetColorAttachmentRendererID());

        // Render Main Camera Framebuffer
    }

    // ///////////////////////////////   RenderSpriteSystem /////////////////////////////// //

    RenderSpriteSystem::RenderSpriteSystem() 
    {
        m_renderCamera = {};
    }


    RenderSpriteSystem::~RenderSpriteSystem() {

    }

    void RenderSpriteSystem::Init() 
    {
    }

    void RenderSpriteSystem::Execute()
    {
        static AssetLibrary* library = AssetLibrary::Get();

        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

        for each (Entity i in scene->GetEntities<SpriteComponent, TransformComponent>())
        {
            if (!i.HasComponent<TransformComponent>()) continue;

            SpriteComponent& spriteRenderer = i.GetComponent<SpriteComponent>();
            TransformComponent& transform = i.GetComponent<TransformComponent>();

            // TODO: load an asset for the uuid 0 for default, so it doesnt crash everywhere
            auto texture = library->GetAsset<Texture>(spriteRenderer.m_textureUUID);

            if (texture == nullptr) continue;

            spriteRenderer.m_mesh->Bind();
            spriteRenderer.m_shader->Bind();

            texture->Bind();

            // TODO: Some material that makes the shader, textures and uniform bindings
            spriteRenderer.m_shader->SetFloat3("m_Color", spriteRenderer.m_color);

            spriteRenderer.m_shader->SetMat4("m_View", m_renderCamera->GetViewMatrix());
            spriteRenderer.m_shader->SetMat4("m_Projection", m_renderCamera->GetProjectionMatrix());
            spriteRenderer.m_shader->SetMat4("m_Transform", transform.m_matrix);

            glDrawElements(GL_TRIANGLES, spriteRenderer.m_mesh->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    }

    // ///////////////////////////////   RenderMeshSystem /////////////////////////////// //

    RenderMeshSystem::RenderMeshSystem() 
    {

    }

    RenderMeshSystem::~RenderMeshSystem() 
    {

    }

    void RenderMeshSystem::Init() 
    {
    }

    void RenderMeshSystem::Execute()
    {
        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

        for each (Entity i in scene->GetEntities<MeshComponent, MeshRenderer>())
        {
            MeshComponent& mesh = i.GetComponent<MeshComponent>();
            MeshRenderer& meshRender = i.GetComponent<MeshRenderer>();

            mesh.m_vertexArray->Bind();
            meshRender.m_shader->Bind();
            meshRender.m_texture->Bind();

            meshRender.m_shader->SetMat4("m_View", m_renderCamera->GetViewMatrix());
            meshRender.m_shader->SetMat4("m_Projection", m_renderCamera->GetProjectionMatrix());

            if (i.HasComponent<TransformComponent>())
            {
                TransformComponent& transform = i.GetComponent<TransformComponent>();
                meshRender.m_shader->SetMat4("m_Transform", transform.m_matrix);
            }
            else
            {
                meshRender.m_shader->SetMat4("m_Transform", glm::identity<glm::mat4x4>());
            }

            glDrawElements(GL_TRIANGLES, mesh.m_vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
        }
    }
}
