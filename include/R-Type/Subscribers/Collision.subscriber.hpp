/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Collision.subscriber.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "ECS/EventSubscriber.hpp"
#include "Engine/Events/Collision.event.hpp"
#include "Engine/Systems/Score.system.hpp"
#include "Engine/Systems/UI.system.hpp"
#include "R-Type/Components/BaseBullet.component.hpp"
#include "R-Type/Components/Booster.component.hpp"
#include "R-Type/Components/BoosterActive.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/Health.component.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Systems/Booster.system.hpp"

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
                using namespace Rtype::Components;

                ECS::World         &world = WORLD;
                Engine::System::UI *ui    = dynamic_cast<Engine::System::UI *>(WORLD.getSystems()["UISystem"].get());
                Engine::System::ScoreSystem *score =
                    dynamic_cast<Engine::System::ScoreSystem *>(WORLD.getSystems()["ScoreSystem"].get());

                if (data.movingEntity->has<PlayerComponent>() && data.collidingEntity->has<EnemyComponent>()) {
                    WORLD.removeEntity(data.movingEntity->getId());
                    ui->handleGameOver(data.movingEntity->getComponent<PlayerComponent>()->playerNb);

                } else if (data.movingEntity->has<BaseBulletComponent>()) {
                    if (data.collidingEntity->has<PlayerComponent, BoosterActiveComponent>()) {
                        auto boosterActive = data.collidingEntity->getComponent<BoosterActiveComponent>();
                        boosterActive->hitpoints -= 1;
                        world.removeEntity(data.movingEntity);

                    } else if (data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                               data.collidingEntity->has<PlayerComponent>()) {
                        WORLD.removeEntity(data.movingEntity->getId());
                        WORLD.removeEntity(data.collidingEntity->getId());
                            ui->handleGameOver(data.collidingEntity->getComponent<PlayerComponent>()->playerNb);

                    } else if (!data.movingEntity->getComponent<BaseBulletComponent>()->fromEnemy &&
                               data.collidingEntity->has<EnemyComponent>()) {
                        score->incrementScore();
                        enemyCollision(data);
                    }
                } else if (data.movingEntity->has<PlayerComponent>() &&
                           data.collidingEntity->has<Components::BoosterComponent>()) {
                    System::BoosterSystem::takeBooster(data.movingEntity, data.collidingEntity);
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
                if (data.movingEntity->getComponent<BaseBulletComponent>()->toDelete)
                    WORLD.removeEntity(data.movingEntity->getId());
            }
    };
} // namespace Rtype::Subscriber
