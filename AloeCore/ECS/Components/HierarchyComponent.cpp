#include "HierarchyComponent.h"

namespace Aloe
{
    HierarchyComponent::HierarchyComponent()
    {
        
    }

    HierarchyComponent::~HierarchyComponent()
    {
        RemoveAllAttachments();
    }

    void HierarchyComponent::SetupAttachment(Entity entity)
    {
        if (IsChild(entity)) return;

        auto& childHC = entity.AddComponent<HierarchyComponent>();

        // Check for infinite loops
        auto parent = GetParent();
        while (parent.IsValid())
        {
            if (parent == entity) return;

            parent = parent.GetComponent<HierarchyComponent>().GetParent();
        }

        // Remove the previous parent
        if (childHC.m_parent.IsValid())
        {
            auto& parentHC = childHC.m_parent.GetComponent<HierarchyComponent>();
            parentHC.m_children.remove(entity);
        }

        // Set the child's parent to this
        childHC.m_parent = GetOwner();

        m_children.push_back(entity);
    }

    void HierarchyComponent::RemoveAttachment(Entity entity)
    {
        m_children.remove(entity);
        entity.GetComponent<HierarchyComponent>().m_parent = Entity();
    }

    void HierarchyComponent::RemoveAllAttachments()
    {
        for (auto& entity : m_children)
        {
            entity.GetComponent<HierarchyComponent>().m_parent = Entity();
        }

        m_children.clear();
    }

    Entity HierarchyComponent::GetParent() const
    {
        return m_parent;
    }

    bool HierarchyComponent::HasChildren() const
    {
        return !m_children.empty();
    }

    bool HierarchyComponent::IsRoot()
    {
        return !m_parent.IsValid();
    }

    std::list<Entity> HierarchyComponent::GetChildren()
    {
        return m_children;
    }

    bool HierarchyComponent::IsChild(Entity& entity)
    {
        return std::find(m_children.begin(), m_children.end(), entity) != std::end(m_children);
    }
}