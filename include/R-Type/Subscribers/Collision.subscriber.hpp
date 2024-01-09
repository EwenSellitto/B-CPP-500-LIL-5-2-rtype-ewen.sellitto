/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Collision.subscriber.hpp
*/

#pragma once

#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Events/Collision.event.hpp"
#include "R-Type/Components/BaseBullet.component.hpp"
#include "R-Type/Components/DeathAnimation.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
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
                    data.movingEntity->removeAllComponents();
                } else if (data.movingEntity->has<BaseBulletComponent>()) {
                    if (data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                        data.collidingEntity->has<PlayerComponent>()) {
                        std::cout << "YOU LOSE" << std::endl;
                        data.movingEntity->removeAllComponents();
                        data.collidingEntity->removeAllComponents();
                    } else if (!data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                               data.collidingEntity->has<EnemyComponent>()) {
                        auto collidingEntity = data.collidingEntity;
                        auto enemyComponent  = collidingEntity->getComponent<EnemyComponent>();
                        auto position        = collidingEntity->getComponent<PositionComponent>();
                        data.movingEntity->removeAllComponents();

                        collidingEntity->removeComponent<AnimationComponent>();
                        collidingEntity->removeComponent<CollisionComponent>();
                        collidingEntity->removeComponent<EnemyAttackComponent>();

                        switch (enemyComponent->enemyType) {
                            case EnemyData::EnemyType::Weak:
                                collidingEntity->addComponent(new DeathAnimationComponent(
                                    "./assets/klaed/Klaed-Fighter-Destruction.png", 0, 0, 64, 64, 64, 64, 100, 9));
                                break;
                            case EnemyData::EnemyType::Medium:
                            case EnemyData::EnemyType::Strong:
                                collidingEntity->removeAllComponents();
                        }

                        return;
                    }
                }
            }
    };
} // namespace Rtype::Subscriber
