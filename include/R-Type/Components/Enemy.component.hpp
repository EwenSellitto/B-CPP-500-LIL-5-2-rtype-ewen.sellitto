/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "R-Type/Systems/Enemy.system.hpp"

namespace Engine::Components
{
    struct EnemyComponent : ECS::BaseComponent {
        public:
            EnemyComponent(EnemyData::EnemyType enemyType) : enemyType(enemyType) {}
            EnemyData::EnemyType enemyType;
    };
} // namespace Engine::Components
