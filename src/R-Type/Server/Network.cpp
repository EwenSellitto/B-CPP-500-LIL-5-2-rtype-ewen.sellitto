/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Engine.cpp
*/

#include "Server/Network.hpp"

#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "R-Type/GameWorld/Entities.hpp"

using namespace Engine;
using namespace ECS;

void ECS::Network::startServerUpdateLoop()
{
    while (running) {
        sendComponentsUpdate();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ECS::Network::connectToServer(const sf::IpAddress &serverAddress, unsigned short port)
{
    thread = std::thread(&Network::sendConnectionToServer, this, serverAddress, port);
}

void ECS::Network::sendConnectionToServer(const sf::IpAddress &serverAddress, unsigned short port)
{
    sf::Packet packet;
    int        packetTypeInt = static_cast<int>(PacketType::Connect);
    packet << packetTypeInt;
    std::cout << "Demande de connexion au serveur " << serverAddress << ":" << port << std::endl;
    if (socket.send(packet, serverAddress, port) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi de la demande de connexion" << std::endl;
    }
    receivePackets();
}

void ECS::Network::sendComponentsUpdate()
{
    ECS::World &world    = Engine::EngineClass::getEngine().world();
    auto       &entities = world.getEntities();

    std::cout << "Sending components update" << std::endl;

    for (auto &pair : entities) { // Supposons que `entities` contienne toutes les entités en jeu
        Entity &entity = *pair.second;
        for (const auto &component : entity.getComponents()) {
            if (component.second->hasChanged()) {
                std::vector<char> componentSerialized = component.second->serialize();

                sf::Packet   packet;
                unsigned int size = static_cast<unsigned int>(componentSerialized.size());
                packet << size;
                if (size > 0) {
                    packet.append(&componentSerialized[0], size);
                }
                component.second->setHasChanged(false);
                for (const auto &client : clientsInfo) {
                    socket.send(packet, client.second.address, client.second.port);
                }
            }
        }
    }
}

void ECS::Network::switchToGame()
{
    using namespace Engine::Components;

    EngineClass &engine = EngineClass::getEngine();
    engine.switchWorld("game");
}