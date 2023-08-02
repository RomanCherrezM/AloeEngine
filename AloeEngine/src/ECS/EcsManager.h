#ifndef _ECS_MANAGER_H_
#define _ECS_MANAGER_H_ 1

#include "ECS/EcsConstants.h"
#include "ECS/ComponentManager.h"
#include "ECS/EntityManager.h"
#include "ECS/SystemManager.h"

#include <memory>

namespace Aloe {

	class ECSManager{
	public:
		void Init(){
			// Create pointers to each manager
			mComponentManager = std::make_unique<ComponentManager>();
			mEntityManager = std::make_unique<EntityManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}

		// Entity methods
		Entity CreateEntity(const char* name = nullptr){
			Entity new_entity = mEntityManager->CreateEntity();
			entities.push_back(new_entity);

			return new_entity;
		}

		void DestroyEntity(Entity entity){
			mEntityManager->DestroyEntity(entity);

			mComponentManager->EntityDestroyed(entity);

			mSystemManager->EntityDestroyed(entity);

			// Delete entities from the current entities list
			entities.remove(entity);
		}


		// Component methods
		template<typename T>
		void RegisterComponent(){
			mComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(Entity entity, T component){
			mComponentManager->AddComponent<T>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(Entity entity){
			mComponentManager->RemoveComponent<T>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T* GetComponent(Entity entity){
			return mComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentType GetComponentType(){
			return mComponentManager->GetComponentType<T>();
		}

		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem(){
			return mSystemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(Signature signature){
			mSystemManager->SetSignature<T>(signature);
		}

		// Entities currently in the ecs
		std::list<Entity> entities;

	private:
		std::unique_ptr<ComponentManager> mComponentManager;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<SystemManager> mSystemManager;
	};
}

#endif