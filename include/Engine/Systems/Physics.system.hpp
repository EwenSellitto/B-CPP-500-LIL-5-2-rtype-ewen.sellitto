/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include <ctime>

namespace Engine::System
{
    class Physics : public ECS::BaseSystem
    {
        public:
            Physics(ECS::World &world) : ECS::BaseSystem(world){};
            Physics(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~Physics() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            //move functions
            void moveTime(ECS::Entity *entity, ECS::ComponentHandle<Components::MovingComponent> handle);

            //collision function
            void collide(ECS::Entity *entity, int x, int y);
    };
} // namespace Engine::System
