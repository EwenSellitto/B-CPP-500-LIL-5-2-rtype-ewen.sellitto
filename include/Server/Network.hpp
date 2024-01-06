#pragma once

#include <SFML/Network.hpp>
#include <iostream>
#include <thread>
#include <unordered_map>

#include "Server/ClientInfo.hpp"
#include "Server/WaitingRoom.hpp"

enum class PacketType {
    Connect,
    Disconnect,
    Lobby,
    INGAME
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

            // ================= INITIALISATION =================

            void startServer(unsigned short port)
            {
                running = true;
                thread  = std::thread(&Network::startClient, this, port);
                std::thread updateThread(&Network::startServerUpdateLoop, this);
                updateThread.detach(); // Vous pouvez également conserver le thread pour le rejoindre plus tard
            }

            void startClient(unsigned short port)
            {
                socket.setBlocking(false);
                if (socket.bind(port) != sf::Socket::Done) {
                    std::cerr << "Erreur de liaison du port " << std::endl;
                    return;
                }
                std::cout << "Client démarré sur le port " << socket.getLocalPort() << std::endl;
                addPlayerToLobby("localhost", port, true);
                while (running) {
                    receivePackets();
                }
                socket.unbind();
            }

            void startServerUpdateLoop();

            void connectToServer(const sf::IpAddress &serverAddress, unsigned short port);
            void sendConnectionToServer(const sf::IpAddress &serverAddress, unsigned short port);

            // ================== ENVOI ==================

            void sendComponentsUpdate();

            void sendPacketTypeToServer(PacketType packetType, const sf::IpAddress &recipient, unsigned short port)
            {
                sf::Packet packet;
                int        packetTypeInt = static_cast<int>(packetType);
                packet << packetTypeInt;
                if (socket.send(packet, recipient, port) != sf::Socket::Done) {
                    std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
                }
            }

            void sendPacketToServer(sf::Packet &packet, const sf::IpAddress &recipient, unsigned short port)
            {
                if (socket.send(packet, recipient, port) != sf::Socket::Done) {
                    std::cerr << "Erreur lors de l'envoi du paquet" << std::endl;
                }
            }

            // ================== RECEPTION ==================

            void receivePackets()
            {
                sf::Packet     packet;
                sf::IpAddress  sender;
                unsigned short senderPort;

                while (running) {
                    while (socket.receive(packet, sender, senderPort) == sf::Socket::Done) {
                        handleReceivedPacket(packet, sender, senderPort);
                    }
                    std::this_thread::sleep_for(
                        std::chrono::milliseconds(10)); // Un petit délai pour ne pas surcharger le CPU
                }
            }

            void handleReceivedPacket(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
            {
                int packetTypeInt;
                packet >> packetTypeInt;
                PacketType packetType = static_cast<PacketType>(packetTypeInt);
                switch (packetType) {
                    case PacketType::Connect:
                        std::cout << "Received connect packet" << std::endl;
                        handleClientConnection(sender, senderPort);
                        break;
                    case PacketType::Disconnect:
                        std::cout << "Received disconnect packet" << std::endl;
                        handleClientDisconnection(sender);
                        break;
                    case PacketType::Lobby:
                        std::cout << "Received lobby packet" << std::endl;
                        break;
                    case PacketType::INGAME:
                        switchToGame();
                        break;
                    default:
                        std::cout << "Received unknown packet" << std::endl;
                        break;
                }
            }

            void stop()
            {
                running = false;
                if (thread.joinable()) thread.join();
            }

        private:
            void handleClientConnection(const sf::IpAddress &clientAddress, unsigned short clientPort)
            {
                sf::Packet responsePacket;
                addPlayerToLobby(clientAddress, clientPort);
                if (waitingRoom.inGame) {
                    responsePacket << static_cast<int>(PacketType::INGAME);
                    switchToGame();
                    std::cout << "Length of clientsInfo: " << clientsInfo.size() << std::endl;
                    for (const auto &client : clientsInfo) {
                        std::cout << "Sending INGAME packet to " << client.second.address << ":" << client.second.port
                                  << std::endl;
                        socket.send(responsePacket, client.second.address, client.second.port);
                    }
                } else {
                    responsePacket << static_cast<int>(PacketType::Lobby);
                    socket.send(responsePacket, clientAddress, clientPort);
                }
            }

            void addPlayerToLobby(const sf::IpAddress &clientAddress, unsigned short clientPort,
                                  bool isCurrentPlayer = false)
            {
                if (clientsInfo.find(clientAddress) != clientsInfo.end()) {
                    std::cerr << "Client already in lobby" << std::endl;
                    return;
                }
                if (!isCurrentPlayer) {
                    clientsInfo.emplace(std::piecewise_construct, std::forward_as_tuple(clientAddress),
                                        std::forward_as_tuple(clientAddress, clientPort, ClientState::InLobby));
                }
                waitingRoom.addPlayer(clientAddress);
            }

            void handleClientDisconnection(const sf::IpAddress &clientAddress)
            {
                clientsInfo.erase(clientAddress);
                waitingRoom.removePlayer(clientAddress);
            }

            void switchToGame();

            WaitingRoom                                                  waitingRoom;
            sf::UdpSocket                                                socket;
            std::unordered_map<sf::IpAddress, ClientInfo, IpAddressHash> clientsInfo;
            std::thread                                                  thread;
            bool                                                         running = true;
    };
} // namespace ECS
