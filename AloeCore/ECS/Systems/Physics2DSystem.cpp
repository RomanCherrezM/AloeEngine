#include "Physics2DSystem.h"

#ifdef _WIN32
#include <windows.h>
#include <libloaderapi.h>
#endif

#include <filesystem>
#include <Core/Script.h>
#include <Core/AloeEngine.h>
#include <Scene/SceneManager.h>
#include <ECS/Components/Components.h>

#include <box2d/box2d.h>

namespace Aloe
{
    const int32_t velocityIterations = 6;
    const int32_t positionIterations = 2;

    Physics2DSystem::Physics2DSystem()
    {

    }

    Physics2DSystem::~Physics2DSystem()
    {

    }

    void Physics2DSystem::Init()
    {

    }

    void Physics2DSystem::Execute()
    {
        if (m_physicsWorld)
        {
            m_physicsWorld->Step(Engine::Get()->GetDeltaTime(), velocityIterations, positionIterations);

            for (auto e : SceneManager::Get().GetCurrentScene()->GetEntities<Rigidbody2DComponent>())
            {
                auto& tr = e.GetComponent<TransformComponent>();
                auto& rb = e.GetComponent<Rigidbody2DComponent>();

                b2Body* body = (b2Body*)rb.m_runtimeBody;
                const auto position = body->GetPosition();
                tr.m_position.x = position.x;
                tr.m_position.y = position.y;
                tr.m_rotation.z = body->GetAngle();
            }
        }
    }

    void Physics2DSystem::OnRuntimeStart()
    {
        m_physicsWorld = new b2World({ 0.0f, -9.8f });

        std::shared_ptr<Scene> scene = SceneManager::Get().GetCurrentScene();

        for (Entity& e : scene->GetEntities<Rigidbody2DComponent>())
        {
            auto& tr = e.GetComponent<TransformComponent>();
            auto& rb = e.GetComponent<Rigidbody2DComponent>();

            b2BodyDef bodyDef;
            bodyDef.type = (b2BodyType)rb.m_type;
            bodyDef.position = { tr.m_position.x, tr.m_position.y };
            bodyDef.angle = tr.m_rotation.z;

            b2Body* body = m_physicsWorld->CreateBody(&bodyDef);
            body->SetFixedRotation(rb.m_fixedRotation);
            rb.m_runtimeBody = body;

            if (e.HasComponent<SquareCollider2DComponent>())
            {
                auto& coll = e.GetComponent<SquareCollider2DComponent>();

                b2PolygonShape boxShape;
                boxShape.SetAsBox(coll.m_size.x * tr.m_scale.x, coll.m_size.y * tr.m_scale.y,
                    b2Vec2(coll.m_offset.x, coll.m_offset.y), 0.0f);

                b2FixtureDef fixtureDef;
                fixtureDef.shape = &boxShape;
                fixtureDef.density = coll.m_density;
                fixtureDef.friction = coll.m_friction;
                fixtureDef.restitution = coll.m_restitution;

                body->CreateFixture(&fixtureDef);
            }
        }
    }

    void Physics2DSystem::OnRuntimeStop()
    {
        delete m_physicsWorld;
        m_physicsWorld = nullptr;
    }
}