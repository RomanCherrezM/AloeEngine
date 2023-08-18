#pragma once

#include <vector>

#include <Scene/Entity.h>

namespace Aloe
{
    enum EEditorEventType
    {
        HierarchyEntitySelected,
        SceneChanged,
    };

#define ALOE_EDITOR_EVENT_CLASS(type) static EEditorEventType GetStaticType() { return EEditorEventType::type; }\

    class EditorEvent
    {
    public:
        virtual ~EditorEvent() = default;

        bool m_handled = false;

        virtual EEditorEventType GetType() const = 0;
    };

    class HierarchyEntitySelectedEvent : public EditorEvent
    {
    public:
        ALOE_EDITOR_EVENT_CLASS(HierarchyEntitySelected);

        HierarchyEntitySelectedEvent(const Entity entity)
            : m_entity(entity) {}

        Entity GetEntity() const { return m_entity; }

        EEditorEventType GetType() const override { return HierarchyEntitySelected; };
    
    private:
        Entity m_entity;
    };

    class SceneChangedEvent : public EditorEvent
    {
    public:
        ALOE_EDITOR_EVENT_CLASS(SceneChanged);

        SceneChangedEvent(std::shared_ptr<Scene>& scene)
            : m_scene(scene) {}

        std::shared_ptr<Scene> GetScene() const { return m_scene; }

        EEditorEventType GetType() const override { return SceneChanged; };

    private:
        std::shared_ptr<Scene>& m_scene;
    };

    class IEditorEventListener {
    public:

        virtual void OnEvent(EditorEvent& event) = 0;

    };

    class EditorEventMessenger : public IEditorEventListener
    {
    public:
        EditorEventMessenger();
        ~EditorEventMessenger();

        void AddListener(IEditorEventListener* listener);
        void RemoveListener(IEditorEventListener* listener);

        void OnEvent(EditorEvent& event);

    private:

        std::vector<IEditorEventListener*> m_listeners;

    };
}