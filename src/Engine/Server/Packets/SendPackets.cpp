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

void ECS::Network::sendUpdatedEntitiesToClients()
{
    sf::Packet packet;
    int        nbEntities = 0;
    packet << static_cast<int>(PacketType::ClientUpdate);

    nbEntities = getNbEntitiesModified();
    packet << nbEntities;
    for (const auto &pair : EngineClass::getEngine().world().getEntities()) {
        addSerializedEntityToPacket(packet, pair);
    }
    sendPacketToAllClients(packet, false);
}

void ECS::Network::sendEventsToServer()
{
    sf::Packet packet;
    int        nbEvents = clientEvents.size();

    if (nbEvents == 0) return;

    packet << static_cast<int>(PacketType::KeyInputs);
    packet << nbEvents;

    for (const auto &event : clientEvents) {
        addSerializedEventToPacket(packet, event);
    }
    clientEvents.clear();
    sendPacketToServer(packet);
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

void ECS::Network::sendPacketToServer(sf::Packet &packet)
{
    if (socket.send(packet, serverHost.first, serverHost.second) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
    }
}

void ECS::Network::sendPacketToAllClients(sf::Packet &packet, bool includeServer)
{
    for (const auto &player : waitingRoom.getPlayers()) {
        if (!includeServer && player->isServer) continue;
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
