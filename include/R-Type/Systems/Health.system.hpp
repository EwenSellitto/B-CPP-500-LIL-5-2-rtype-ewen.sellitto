/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Health.system.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Rtype::Systems
{
    class HealthSystem : public ECS::BaseSystem
    {
        public:
            HealthSystem(ECS::World &world) : ECS::BaseSystem(world){};
            HealthSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~HealthSystem() override = default;

            void configure(ECS::World &world) override {}
            void unconfigure() override {}

            void tick() override;
    };
} // namespace Rtype::Systems
