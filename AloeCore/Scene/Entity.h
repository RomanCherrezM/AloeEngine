#pragma once

#include <entt.hpp>

#include <Scene/Scene.h>

namespace Aloe
{
	class Scene;

    class Entity
    {
    public:
        Entity() = default;
		~Entity();
        Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>()) return GetComponent<T>();
			T& component = m_scene->m_registry.emplace<T>(m_handler, std::forward<Args>(args)...);
			component.Initialize(*this);
			return component;
		}

		template<typename T, typename... Args>
		T& ReplaceComponent(Args&&... args)
		{
			T& component = m_scene->m_registry.emplace_or_replace<T>(m_handler, std::forward<Args>(args)...);
			component.Initialize(*this);
			return component;
		}

		template<typename T>
		T& GetComponent()
		{
			// Assert HasComponent
			return m_scene->m_registry.get<T>(m_handler);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_scene->m_registry.all_of<T>(m_handler);
		}

		template<typename T>
		void RemoveComponent()
		{
			// Assert HasComponent
			m_scene->m_registry.remove<T>(m_handler);
		}

		bool IsValid() { return m_handler != entt::null && m_scene != nullptr; }

		operator bool() const { return m_handler != entt::null; }
		operator entt::entity() const { return m_handler; }
		operator uint32_t() const { return (uint32_t)m_handler; }
		bool operator==(const Entity& other) const
		{
			return m_handler == other.m_handler && m_scene == other.m_scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}

    private:

        entt::entity m_handler = entt::null;
        Scene* m_scene = nullptr;

		friend class Scene;
    };
}