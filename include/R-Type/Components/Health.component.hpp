/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Health.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    struct HealthComponent : ECS::BaseComponent {
        public:
            HealthComponent(int health) : health(health) {}

            int health;
    };
} // namespace Rtype::Components
