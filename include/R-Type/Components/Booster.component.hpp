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

    enum class WeaponType {
        BASIC,
        CANON,
        LASER
    };

    struct WeaponBoosterComponent : ECS::BaseComponent {
        public:
            WeaponBoosterComponent(WeaponType type) : type(type){};
            ~WeaponBoosterComponent() override = default;

            WeaponType type;
    };

} // namespace Rtype::Components
