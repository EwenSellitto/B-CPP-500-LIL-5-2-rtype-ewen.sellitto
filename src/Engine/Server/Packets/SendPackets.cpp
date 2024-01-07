/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** SendPackets
*/

#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Server/Network.hpp"
#include "R-Type/GameWorld/Entities.hpp"

using namespace Engine;
using namespace ECS;

void ECS::Network::sendComponentsUpdate()
{
    ECS::World &world    = Engine::EngineClass::getEngine().world();
    auto       &entities = world.getEntities();

    // std::cout << "Sending components update" << std::endl;

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
                sendPacketToAllClients(packet);
            }
        }
    }
}

void ECS::Network::sendPacketTypeToServer(PacketType packetType, const sf::IpAddress &recipient, unsigned short port)
{
    sf::Packet packet;
    int        packetTypeInt = static_cast<int>(packetType);
    packet << packetTypeInt;
    if (socket.send(packet, recipient, port) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
    }
}

void ECS::Network::sendPacketToServer(sf::Packet &packet, const sf::IpAddress &recipient, unsigned short port)
{
    if (socket.send(packet, recipient, port) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
    }
}

void ECS::Network::sendPacketToAllClients(sf::Packet &packet)
{
    for (const auto &player : waitingRoom.getPlayers()) {
        if (socket.send(packet, player.address, player.port) != sf::Socket::Done) {
            std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
        }
    }
}

void ECS::Network::sendPacketToClient(sf::Packet &packet, const sf::IpAddress &address, unsigned short port)
{
    if (socket.send(packet, address, port) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
    }
}

void ECS::Network::addSerializedComponentToPacket(sf::Packet &packet, ECS::BaseComponent *component)
{
    if (component == nullptr) {
        std::cerr << "Component is null" << std::endl;
        return;
    }

    std::vector<char> serializedData = component->serialize();
    int               serializedSize = static_cast<int>(serializedData.size());

    packet << serializedSize;
    if (serializedSize > 0) {
        for (char byte : serializedData) {
            packet << static_cast<sf::Uint8>(byte);
        }
    }
}
