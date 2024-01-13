/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Collision.subscriber.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Events/Collision.event.hpp"
#include "R-Type/Components/BaseBullet.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/Health.component.hpp"
#include "R-Type/Components/Player.component.hpp"

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
                    WORLD.removeEntity(data.movingEntity->getId());
                } else if (data.movingEntity->has<BaseBulletComponent>()) {
                    if (data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<PlayerComponent>()) {
                        std::cout << "YOU LOSE" << std::endl;
                        WORLD.removeEntity(data.movingEntity->getId());
                        WORLD.removeEntity(data.collidingEntity->getId());
                    } else if (!data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                               data.collidingEntity->has<EnemyComponent>()) {
                        enemyCollision(data);
                    }
                }
            }

        private:
            void enemyCollision(const CollisionEvent &data)
            {
                using namespace Engine::Components;
                using namespace Rtype::Components;

                auto                                  collidingEntity = data.collidingEntity;
                ECS::ComponentHandle<HealthComponent> health;

                if (collidingEntity->has<HealthComponent>()) {
                    health      = collidingEntity->getComponent<HealthComponent>();
                    auto damage = data.movingEntity->getComponent<BaseBulletComponent>()->damage;

                    health->health -= damage;
                } else {
                    WORLD.removeEntity(data.collidingEntity->getId());
                }
                WORLD.removeEntity(data.collidingEntity->getId());
                data.movingEntity->removeAllComponents();
            }
    };
} // namespace Rtype::Subscriber
