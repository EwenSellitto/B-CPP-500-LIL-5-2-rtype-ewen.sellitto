/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Booster.system.hpp
*/

#pragma once

#include "ECS/System.hpp"

namespace Rtype::System
{
    class BoosterSystem : ECS::BaseSystem
    {
        public:
            BoosterSystem(ECS::World &world) : ECS::BaseSystem(world) {}
            BoosterSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~BoosterSystem() override = default;

            void configure([[maybe_unused]] ECS::World &world) override {}
            void unconfigure() override {}

            void tick() override;
    };
} // namespace Rtype::System
