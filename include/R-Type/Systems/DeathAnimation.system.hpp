/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** DeathAnimation.system.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class DeathAnimationSystem : public ECS::BaseSystem
    {
        public:
            DeathAnimationSystem(ECS::World &world) : ECS::BaseSystem(world) {}
            DeathAnimationSystem(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~DeathAnimationSystem() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;
    };
} // namespace Engine::System
