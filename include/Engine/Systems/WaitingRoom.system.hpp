/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include <boost/array.hpp>
#include <iostream>
#include <map>

#include "ECS/System.hpp"
#include "ECS/World.hpp"

namespace Engine::System
{

    class WaitingRoom : public ECS::BaseSystem
    {
        public:
            WaitingRoom(ECS::World &world) : ECS::BaseSystem(world){};
            WaitingRoom(ECS::World &world, id_t ids...) : ECS::BaseSystem(world, ids) {}
            ~WaitingRoom() override = default;

            void        configure(ECS::World &world) override;
            void        unconfigure() override;
            void        addPlayer(int id, std::string name);
            void        removePlayer(int id);
            std::string getPlayers(int id);
            void        tick() override;

        private:
            std::map<int, std::string> _players;
    };
} // namespace Engine::System
