/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** BoosterActive.component.hpp
*/

#pragma once

#include "ECS/Components.hpp"
#include "SFML/System/Clock.hpp"

namespace Rtype::Components
{
    struct BoosterActiveComponent : ECS::BaseComponent {
            BoosterActiveComponent(int duration) : duration(duration), clock({}) {}
            ~BoosterActiveComponent() override = default;

            int       duration;
            int       hitpoints = 3;
            sf::Clock clock;
    };

} // namespace Rtype::Components
