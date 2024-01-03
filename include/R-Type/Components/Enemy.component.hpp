/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include <string>

#include "ECS/Components.hpp"
#include "R-Type/Systems/Enemy.system.hpp"

namespace Engine::Components
{
    struct EnemyComponent : ECS::BaseComponent {
        public:
            EnemyComponent(int health, EnemyData::EnemyType enemyType) : health(health), enemyType(enemyType) {}

            ~EnemyComponent() override = default;

            std::vector<char> serialize(void) override
            {
                return std::vector<char>();
            }

            int                  health;
            EnemyData::EnemyType enemyType;
    };
} // namespace Engine::Components
