/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** HandlePackets
*/

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

template <typename T>
ECS::BaseComponent *ECS::Network::deserializeComponent(const std::vector<char> &serialized, T componentType)
{
    using namespace Engine::Components;

    if (componentType == ComponentHandle<PositionComponent>()) {
        PositionComponent *component = new PositionComponent(0, 0);
        return component->deserialize(serialized);
    }

    return nullptr;
}

void ECS::Network::handleInitializeGame(sf::Packet &packet)
{
    using namespace Engine::Components;
    int               nbPlayers;
    int               serialisedSize;
    std::vector<char> serialised;

    // Extraire le nombre de joueurs
    packet >> nbPlayers;

    // Extraire la taille des données sérialisées
    packet >> serialisedSize;

    // Vérifier que la taille sérialisée est valide
    if (serialisedSize > 0 && static_cast<std::size_t>(serialisedSize) <= packet.getDataSize()) {
        serialised.resize(serialisedSize);

        // Extraire les données sérialisées
        for (int i = 0; i < serialisedSize; ++i) {
            sf::Uint8 dataByte;
            packet >> dataByte;
            serialised[i] = static_cast<char>(dataByte);
        }

        auto positionComp =
            dynamic_cast<PositionComponent *>(deserializeComponent(serialised, ComponentHandle<PositionComponent>()));

        std::cout << "Received InitializeGame" << std::endl;
        std::cout << "Nb players: " << nbPlayers << std::endl;
        std::cout << "Serialised size: " << serialisedSize << std::endl;
        std::cout << "Deserialized: " << positionComp->x << ", " << positionComp->y << std::endl;

        // switchToGame();  // Décommenter si nécessaire
    } else {
        std::cerr << "Invalid serialized data size" << std::endl;
    }
}
