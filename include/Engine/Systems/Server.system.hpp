/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <map>

#include "ECS/System.hpp"
#include "ECS/World.hpp"
#include "Engine/Systems/WaitingRoom.system.hpp"

using boost::asio::ip::udp;
namespace Engine::System
{

    class Server : public ECS::BaseSystem
    {
        public:
            Server(ECS::World &world)
                : ECS::BaseSystem(world), socket_(this->io_context_, udp::endpoint(udp::v4(), 8081)){};
            Server(ECS::World &world, id_t ids...)
                : ECS::BaseSystem(world, ids), socket_(this->io_context_, udp::endpoint(udp::v4(), 8081))
            {
            }
            ~Server() override;

            void configure(ECS::World &world) override;
            void unconfigure() override;
            void StartReceive();
            void handle_receive(const boost::system::error_code &error, std::size_t bytes_transferred);
            void run(std::string message);
            void handle_send(std::string /*message*/, const boost::system::error_code & /*error*/,
                             std::size_t /*bytes_transferred*/);

            void tick() override;

        private:
            boost::asio::io_context  io_context_;
            udp::socket              socket_;
            udp::endpoint            remote_endpoint_;
            boost::array<char, 1024> recvbuffer;
    };
} // namespace Engine::System
