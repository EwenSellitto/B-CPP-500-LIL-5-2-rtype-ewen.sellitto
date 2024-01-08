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

void ECS::Network::sendComponentsUpdate() {}

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
        if (socket.send(packet, player->address, player->port) != sf::Socket::Done) {
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
    ComponentType     componentType  = component->getType();
    int               serializedSize = static_cast<int>(serializedData.size());

    packet << static_cast<int>(componentType);
    packet << serializedSize;
    if (serializedSize > 0) {
        for (char byte : serializedData) {
            packet << static_cast<sf::Uint8>(byte);
        }
    }
}

void ECS::Network::addSerializedEntityToPacket(sf::Packet                                                     &packet,
                                               const std::pair<const ECS::id_t, std::unique_ptr<ECS::Entity>> &pair)
{
    int nbChangedComponents = 0;

    if (pair.second == nullptr) return;

    for (const auto &component : pair.second->getComponents()) {
        if (component.second->getType() != ComponentType::NoneComponent && component.second->hasChanged()) {
            nbChangedComponents++;
        }
    }
    if (nbChangedComponents == 0) return;

    packet << static_cast<sf::Uint64>(pair.first);
    packet << nbChangedComponents;
    for (const auto &component : pair.second->getComponents()) {
        if (component.second->hasChanged()) {
            if (component.second->getType() == ComponentType::NoneComponent) continue;
            addSerializedComponentToPacket(packet, component.second.get());
            component.second->setHasChanged(false);
        }
    }
}
