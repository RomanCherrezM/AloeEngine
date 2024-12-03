#include "TransformSystem.h"

#include <Scene/SceneManager.h>

namespace Aloe {

    TransformSystem::TransformSystem()
    {
    }

    TransformSystem::~TransformSystem()
    {
    }

    void TransformSystem::Init()
    {
    }

    void TransformSystem::Execute()
    {
        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

        for (Entity entity : scene->GetEntities<TransformComponent>())
        {
            TransformComponent& trParent = entity.GetComponent<TransformComponent>();

            if (entity.HasComponent<HierarchyComponent>())
            {
                HierarchyComponent& hierarchy = entity.GetComponent<HierarchyComponent>();

                // Check for root hierarchy components
                if (hierarchy.IsRoot())
                {
                    trParent.m_matrix =
                        glm::translate(glm::mat4(1.0f), trParent.m_position) *
                        glm::toMat4(glm::quat(trParent.m_rotation)) *
                        glm::scale(glm::mat4(1.0f), trParent.m_scale);

                    for (Entity child : hierarchy.GetChildren())
                    {
                        TransformComponent& tr = child.GetComponent<TransformComponent>();
                        ApplyTransformation(tr, trParent);
                    }
                }
            }
            else
            {
                trParent.m_matrix =
                    glm::translate(glm::mat4(1.0f), trParent.m_position) *
                    glm::toMat4(glm::quat(trParent.m_rotation)) *
                    glm::scale(glm::mat4(1.0f), trParent.m_scale);
            }
        }
    }

    void TransformSystem::OnEvent(Event& event)
    {
        
    }

    void TransformSystem::ApplyTransformation(TransformComponent& tr, TransformComponent& trParent)
    {
        // Compute local transform matrix from position, rotation, and scale
        glm::mat4 matrix =
            glm::translate(glm::mat4(1.0f), tr.m_position) *
            glm::toMat4(glm::quat(tr.m_rotation)) *
            glm::scale(glm::mat4(1.0f), tr.m_scale);

        // Combine with parent's world matrix
        tr.m_matrix = trParent.m_matrix * matrix;

        // Apply the same for all children
        HierarchyComponent& childHC = tr.GetOwner().GetComponent<HierarchyComponent>();
        for(Entity child : childHC.GetChildren()) {

            TransformComponent& childTr = child.GetComponent<TransformComponent>();

            ApplyTransformation(childTr, tr);
        }
    }

}