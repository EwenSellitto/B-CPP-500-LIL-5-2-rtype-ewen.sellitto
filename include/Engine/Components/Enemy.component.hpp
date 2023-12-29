/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "Engine/Systems/Enemy.system.hpp"
#include <string>

namespace Engine::Components
{
    struct EnemyComponent : ECS::BaseComponent {
        public:

            EnemyComponent(int health, EnemyType enemyType)
                : health(health), enemyType(enemyType) {}
            int health;
            EnemyType enemyType;
    };
} // namespace Engine::Components
