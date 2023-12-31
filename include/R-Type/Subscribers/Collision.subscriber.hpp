/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Collision.subscriber.hpp
*/

#pragma once

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Bullet.component.hpp"
#include "Engine/Components/Enemy.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Events/Collision.event.hpp"

namespace Rtype::Subscriber
{
    class CollisionEventSubscriber : public virtual ECS::EventSubscriber<CollisionEvent>
    {
        public:
            CollisionEventSubscriber()           = default;
            ~CollisionEventSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const CollisionEvent &data) override
            {
                using namespace Engine::Components;
                if (data.movingEntity->has<BulletComponent>() && data.collidingEntity->has<EnemyComponent>()) {

                    for (auto &entity : Engine::EngineClass::getEngine().world().getEntities()) {
                        std::cout << "entity id: " << entity.first << std::endl;
                        if (entity.second.get() == data.movingEntity) {
                            std::cout << "found the entity" << std::endl;
                            std::cout << "entity id: " << entity.first << std::endl;
                        }
                    }
                    std::cout << "hit ! " << std::endl;
                }
                data.movingEntity->removeComponent<MovingComponent>();
            }
    };
} // namespace Rtype::Subscriber
