/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Booster.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"

namespace Rtype::Components
{
    struct BoosterComponent : ECS::BaseComponent {
        public:
            BoosterComponent(int duration) : duration_seconds(duration){};
            ~BoosterComponent() override = default;

            int duration_seconds;
    };

    struct isBoosterComponent : ECS::BaseComponent {
        public:
            isBoosterComponent()           = default;
            ~isBoosterComponent() override = default;
    };

} // namespace Rtype::Components
