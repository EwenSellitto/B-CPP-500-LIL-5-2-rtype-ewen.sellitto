/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine
{
    namespace System
    {
        class Renderer : public ECS::BaseSystem
        {
            public:
                Renderer(ECS::World &world) : ECS::BaseSystem(world){};
                Renderer(ECS::World &world, id_t ids...) : ECS::BaseSystem(world, ids) {}
                ~Renderer() override = default;

                void configure(ECS::World &world) override;

                void unconfigure() override;

                void tick() override;
        };
    } // namespace System
} // namespace Engine