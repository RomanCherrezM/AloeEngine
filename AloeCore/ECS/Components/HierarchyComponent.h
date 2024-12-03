#pragma once

#include "Component.h"

#include <Scene/Entity.h>

namespace Aloe
{
    class HierarchyComponent : public Component
    {
    public:

        HierarchyComponent();
        ~HierarchyComponent();

        // Handles an attachment of parent child, checks for
        // other existing attachments and undoes them, also
        // checks for infinite loops in the attachment, etc...
        void SetupAttachment(Entity entity);
        
        void RemoveAttachment(Entity entity);

        void RemoveAllAttachments();

        Entity GetParent() const;

        bool HasChildren() const;

        bool IsRoot();

        std::list<Entity> GetChildren();

    private:

        bool IsChild(Entity& entity);

        Entity m_parent;
        std::list<Entity> m_children;

    };
}