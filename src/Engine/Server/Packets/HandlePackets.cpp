/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** HandlePackets
*/

#include <typeindex>

#include "Engine/Server/Network.hpp"

void ECS::Network::handleHandshakeRequest(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
{
    handleClientConnection(packet, sender, senderPort);
}

void ECS::Network::handleHandshakeResponse(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
{
    std::cout << "Received HandshakeResponse" << std::endl;
}

void ECS::Network::handleLeaveLobby(sf::Packet &packet, const sf::IpAddress &sender)
{
    waitingRoom.removePlayer(sender);
}

void ECS::Network::handleInitializeGame(sf::Packet &packet)
{
    using namespace Engine::Components;
    int               nbPlayers;
    int               serialisedSize;
    int     componentType;
    std::vector<char> serialised;

    packet >> componentType;

    packet >> nbPlayers;

    packet >> serialisedSize;

    std::cout << componentType << std::endl;
    std::cout << nbPlayers << std::endl;
    std::cout << serialisedSize << std::endl;

    if (serialisedSize > 0 && static_cast<std::size_t>(serialisedSize) <= packet.getDataSize()) {
        serialised.resize(serialisedSize);

        for (int i = 0; i < serialisedSize; ++i) {
            sf::Uint8 dataByte;
            packet >> dataByte;
            serialised[i] = static_cast<char>(dataByte);
        }

        ECS::BaseComponent *comp = this->componentsConvertor.createComponent(static_cast<ComponentType>(componentType))
                                       ->deserialize(serialised, nullptr);

        std::cout << "Received InitializeGame" << std::endl;
        std::cout << "Nb players: " << nbPlayers << std::endl;
        std::cout << "Serialised size: " << serialisedSize << std::endl;
        auto *compPos = dynamic_cast<PositionComponent *>(comp);
        std::cout << "Deserialized: " << compPos->x << ", " << compPos->y << std::endl;

        // switchToGame();  // Décommenter si nécessaire
    } else {
        std::cerr << "Invalid serialized data size" << std::endl;
    }
}
