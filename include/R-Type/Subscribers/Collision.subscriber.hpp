/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Collision.subscriber.hpp
*/

#pragma once

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Events/Collision.event.hpp"
#include "R-Type/Components/BaseBullet.component.hpp"

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

                if (data.movingEntity->has<PlayerComponent>() && data.collidingEntity->has<EnemyComponent>()) {
                    std::cout << "YOU LOSE" << std::endl;
                    data.movingEntity->removeAllComponents();
                    return;
                }
                if (data.movingEntity->has<BaseBulletComponent>()) {
                    if (data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<PlayerComponent>()) {
                        std::cout << "YOU LOSE" << std::endl;
                        data.movingEntity->removeAllComponents();
                        data.collidingEntity->removeAllComponents();
                        return;
                    }
                    if (!data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<EnemyComponent>()) {
                        data.movingEntity->removeAllComponents();
                        data.collidingEntity->removeAllComponents();
                        return;
                    }
                }
            }
    };
} // namespace Rtype::Subscriber
