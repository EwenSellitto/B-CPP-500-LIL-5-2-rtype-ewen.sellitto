/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include <SFML/Window/Event.hpp>

#include "ECS/Entity.hpp"
#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{
    class MovePlayer : public ECS::BaseSystem
    {
        public:
            MovePlayer(ECS::World &world) : ECS::BaseSystem(world){};
            MovePlayer(ECS::World &world, ECS::id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~MovePlayer() override = default;

            void configure(ECS::World &world) override;

            void unconfigure() override;

            void tick() override;

            void addMovePlayer(sf::Event::KeyEvent key);
            void stopMovePlayer(sf::Event::KeyEvent key);

            // TODO: if the entity get destroyed, this will crash.

            void setCurrentPlayer(ECS::Entity *entity);
            void setPlayerSpeed(float newSpeed);

            ECS::Entity *player = nullptr;
            float        speed  = 10;
    };
} // namespace Engine::System
