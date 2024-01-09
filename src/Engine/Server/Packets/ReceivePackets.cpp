/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ReceivePackets
*/

#include <functional>
#include <unordered_map>

#include "Engine/Server/Network.hpp"

void ECS::Network::receivePackets()
{
    sf::Packet     packet;
    sf::IpAddress  sender;
    unsigned short senderPort;
    while (running) {
        while (socket.receive(packet, sender, senderPort) == sf::Socket::Done) {
            handleReceivedPacket(packet, sender, senderPort);
        }
        if (isServer && waitingRoom.isGameStarted()) {
            sendUpdatedEntitiesToClients();
        }
        if (!isServer && gameHasStarted) {
            sendEventsToServer();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Un petit délai pour ne pas surcharger le CPU
    }
}

void ECS::Network::handleReceivedPacket(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
{
    int packetTypeInt;
    packet >> packetTypeInt;
    PacketType packetType = static_cast<PacketType>(packetTypeInt);
    switch (packetType) {
        case PacketType::HandshakeRequest:
            handleHandshakeRequest(packet, sender, senderPort);
            break;
        case PacketType::HandshakeResponse:
            break;
        case PacketType::LeaveLobby:
            handleLeaveLobby(packet, sender);
            break;
        case PacketType::SwitchWorld:
            handleSwitchWorld(sender, senderPort);
            break;
        case PacketType::SwitchWorldOkForMe:
            handleReceiveSwitchedWorld(sender, senderPort);
            break;
        case PacketType::ClientIndependentInitialization:
            handleClientIndependentInitialization(packet);
            break;
        case PacketType::InitializeGame:
            handleInitializeGame(packet, sender, senderPort);
            break;
        case PacketType::InitializeGameOkForMe:
            handleReceiveInitializedGame(sender, senderPort);
            break;
        case PacketType::KeyInputs:
            handleKeyInputs(packet, sender, senderPort);
            break;
        case PacketType::LaunchGame:
            std::cout << "Received LaunchGame" << std::endl;
            gameHasStarted = true;
            break;
        case PacketType::ClientUpdate:
            handleClientUpdate(packet, sender, senderPort);
            break;
        default:
            std::cout << static_cast<int>(packetType) << std::endl;
            std::cerr << "Paquet reçu inconnu" << std::endl;
            break;
    }
}