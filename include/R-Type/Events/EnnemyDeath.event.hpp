/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** EnnemyDeath.event.hpp
*/

#pragma once

#include "ECS/Entity.hpp"

namespace Rtype::Events
{
    struct EnnemyDeath {
        public:
            EnnemyDeath(ECS::Entity *enemy) : Enemy(enemy) {}
            ~EnnemyDeath() = default;

            ECS::Entity *Enemy;
    };
} // namespace Rtype::Events
