#pragma once

#include <Scene/Entity.h>

namespace Aloe
{
    struct HierarchyComponent
    {
        Entity m_entity;
        HierarchyComponent* m_parentComponent = nullptr;
        std::list<HierarchyComponent*> m_childrenComponent;

        bool IsParentInHierarchy(HierarchyComponent* parentComponent)
        {
            HierarchyComponent* itComponent = m_parentComponent;
            while (itComponent != nullptr)
            {
                if (itComponent == parentComponent)
                {
                    return true;
                }

                itComponent = itComponent->GetParent();
            }

            return false;
        }

        HierarchyComponent* GetParent()
        {
            return m_parentComponent;
        }

        // Adds a new child to this component, removing it from previous parent
        bool AddAttachment(HierarchyComponent* childComponent)
        {
            // Check if its already a child of this component

            // If not get its parent, if has parent, remove it from its children
            HierarchyComponent* parentHC = childComponent->GetParent();
            if (parentHC != nullptr)
            {
                parentHC->RemoveAttachment(childComponent);
            }

            m_childrenComponent.push_back(childComponent);
            childComponent->m_parentComponent = this;

            return true;
        }

        bool RemoveAttachment(HierarchyComponent* childComponent)
        {
            // Find in the children and remove it
            if (std::find(m_childrenComponent.begin(), m_childrenComponent.end(), childComponent) != std::end(m_childrenComponent))
            {
                childComponent->m_parentComponent = nullptr;
                m_childrenComponent.remove(childComponent);
                return true;
            }

            return false;
        }
    
        // Getters
        bool HasChildren()
        {
            return m_childrenComponent.empty();
        }
    };
}