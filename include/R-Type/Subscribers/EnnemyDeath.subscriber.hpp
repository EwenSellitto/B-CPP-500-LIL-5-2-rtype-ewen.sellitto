/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** EnemyDeath.subscriber.hpp
*/

#pragma once

#include <iostream>

#include "ECS/Components.hpp"
#include "ECS/EventSubscriber.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "R-Type/Components/Booster.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Events/EnnemyDeath.event.hpp"
#include "R-Type/Systems/Enemy.system.hpp"

namespace Rtype::Subscribers
{
    class EnnemyDeathSubscriber : public ECS::EventSubscriber<Rtype::Events::EnnemyDeath>
    {
        public:
            EnnemyDeathSubscriber()           = default;
            ~EnnemyDeathSubscriber() override = default;
            void receiveEvent([[maybe_unused]] const std::string &name, const Rtype::Events::EnnemyDeath &data) override
            {
                std::cout << "EnnemyDeathSubscriber" << std::endl;
                ECS::ComponentHandle<Engine::Components::PositionComponent> position;
                ECS::ComponentHandle<Engine::Components::EnemyComponent>    enemy;

                if (!(data.Enemy->has<Engine::Components::PositionComponent>() &&
                      data.Enemy->has<Engine::Components::EnemyComponent>()))
                    return;
                position = data.Enemy->getComponent<Engine::Components::PositionComponent>();
                enemy    = data.Enemy->getComponent<Engine::Components::EnemyComponent>();
                if (enemy->enemyType == EnemyData::EnemyType::Medium) {
                    WORLD.createEntity(
                        new Engine::Components::PositionComponent(position->x, position->y),
                        new Rtype::Components::BoosterComponent(10),
                        new Engine::Components::RenderableComponent(
                            "../../../assets/Pickup/PickupIcon-ShieldGenerator-Allaroundshield.png", 0, 0, 1),
                        new Engine::Components::AnimationComponent(0, 0, 48, 48, 48, 48, 100, 15));
                }
            }
    };
} // namespace Rtype::Subscribers
