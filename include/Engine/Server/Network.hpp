/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** RenderEngine.hpp
*/

#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "ECS/Components.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Server/WaitingRoom.hpp"
#include "public/AvailableComponents.hpp"

enum class PacketType {
    HandshakeRequest,
    HandshakeResponse,
    LeaveLobby,
    LeaveLobbyResponse,
    InitializeGame,
    ClientUpdate,
    ClientUpdateACK,
    GlobalState,
    PlayerAction,
    ActionOutcome,
    Heartbeat,
    PlayerDisconnected,
    Error,
    ErrorAcknowledged,
    EndGame,
    EndGameAcknowledged,
};

struct IpAddressHash {
        std::size_t operator()(const sf::IpAddress &ip) const
        {
            return std::hash<std::string>()(ip.toString());
        }
};
namespace ECS
{
    class Network
    {
        public:
            Network() = default;

            // =========================================================
            // ==================== SERVER HANDLER =====================
            // =========================================================

            void startServer(unsigned short port);
            void startClient(unsigned short port);
            void startServerUpdateLoop();

            void connectToServer(const sf::IpAddress &serverAddress, unsigned short port);
            void sendConnectionToServer(const sf::IpAddress &serverAddress, unsigned short port);

            void stop();

            // =========================================================
            // ======================= ENVOI ===========================
            // =========================================================

            void sendComponentsUpdate();
            void addSerializedComponentToPacket(sf::Packet &packet, ECS::BaseComponent *component);
            void sendPacketTypeToServer(PacketType packetType, const sf::IpAddress &recipient, unsigned short port);
            void sendPacketToServer(sf::Packet &packet, const sf::IpAddress &recipient, unsigned short port);

            void sendPacketToAllClients(sf::Packet &packet);
            void sendPacketToClient(sf::Packet &packet, const sf::IpAddress &address, unsigned short port);

            // =========================================================
            // ====================== RECEPTION ========================
            // =========================================================

            void receivePackets();
            void handleReceivedPacket(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort);
            template <typename T>
            ECS::BaseComponent *deserializeComponent(const std::vector<char> &serialized, T componentType);

        private:
            // =========================================================
            // ================== GESTION DES CLIENTS ==================
            // =========================================================

            // Méthode pour gérer la connexion d'un client
            void handleClientConnection(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
            {
                sf::Packet responsePacket;
                responsePacket << static_cast<int>(PacketType::HandshakeResponse) << true;
                sendPacketToClient(responsePacket, sender, senderPort);
                addPlayerToLobby(sender, senderPort);
            }

            void addPlayerToLobby(const sf::IpAddress &clientAddress, unsigned short clientPort)
            {
                waitingRoom.addPlayer(clientAddress, clientPort);
                // Si tous les joueurs sont connectés, envoyer les informations du lobby
                std::cout << "Nb players: " << waitingRoom.getPlayers().size() << std::endl;
                if (waitingRoom.isReadyToStart()) {
                    for (const auto &client : waitingRoom.getPlayers()) {
                        sf::Packet packet;
                        packet << static_cast<int>(PacketType::InitializeGame);
                        auto positionComp = new Engine::Components::PositionComponent(123, 340);
                        packet << static_cast<int>(ComponentType::PositionComponent);
                        packet << static_cast<int>(waitingRoom.getPlayers().size());
                        addSerializedComponentToPacket(packet, positionComp);
                        sendPacketToClient(packet, client.address, client.port);
                    }
                }
            }

            void switchToGame();

            // =========================================================
            // ================== GESTION DES PAQUETS ==================
            // =========================================================

            void handleHandshakeRequest(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort);
            void handleHandshakeResponse(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort);

            void handleLeaveLobby(sf::Packet &packet, const sf::IpAddress &sender);

            void handleInitializeGame(sf::Packet &packet);

            // ================== ATTRIBUTS ==================

            WaitingRoom         waitingRoom;
            sf::UdpSocket       socket;
            std::thread         thread;
            bool                running = true;
            ComponentsConvertor componentsConvertor;
    };
} // namespace ECS
