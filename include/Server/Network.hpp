#include <SFML/Network.hpp>
#include <iostream>
#include <unordered_map>

#include "Server/ClientInfo.hpp"
#include "Server/WaitingRoom.hpp"

enum class PacketType {
    Connect,
    Disconnect,
    Lobby,
    GAME
};

struct IpAddressHash {
        std::size_t operator()(const sf::IpAddress &ip) const
        {
            return std::hash<std::string>()(ip.toString());
        }
};

class Network
{
    public:
        Network() : isServer(false) {}

        void startServer(unsigned short port)
        {
            socket.setBlocking(false);
            if (socket.bind(port) != sf::Socket::Done) {
                std::cerr << "Erreur de liaison du port " << port << std::endl;
                return;
            }
            std::cout << "Serveur démarré sur le port " << port << std::endl;
            while (running) {
                receivePackets();
            }
            socket.unbind();
        }

        void connectToServer(const sf::IpAddress &serverAddress, unsigned short port)
        {
            sf::Packet packet;
            int        packetTypeInt = static_cast<int>(PacketType::Connect);
            packet << packetTypeInt;

            std::cout << "Demande de connexion au serveur " << serverAddress << ":" << port << std::endl;

            if (socket.send(packet, serverAddress, port) != sf::Socket::Done) {
                std::cerr << "Erreur lors de l'envoi de la demande de connexion" << std::endl;
            }
        }

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

        void receivePackets()
        {

            sf::Packet     packet;
            sf::IpAddress  sender;
            unsigned short senderPort;

            while (socket.receive(packet, sender, senderPort) == sf::Socket::Done) {

                int packetTypeInt;
                packet >> packetTypeInt;

                PacketType packetType = static_cast<PacketType>(packetTypeInt);

                switch (packetType) {
                    case PacketType::Connect:
                        std::cout << "Nouveau client connecté : " << sender << ":" << senderPort << std::endl;
                        handleClientConnection(sender, senderPort);
                        break;
                    case PacketType::Disconnect:
                        std::cout << "Client déconnecté : " << sender << ":" << senderPort << std::endl;
                        handleClientDisconnection(sender);
                        break;
                    default:
                        std::cout << "Received unknown packet" << std::endl;
                        break;
                }
            }
        }

        // Envoyer des mises à jour
        void sendUpdates()
        {
            // Logique pour envoyer des mises à jour aux clients
        }

        // Gérer les salles d'attente
        void manageLobby()
        {
            // Logique pour gérer les salles d'attente
        }

    private:
        void handleClientConnection(const sf::IpAddress &clientAddress, unsigned short clientPort)
        {
            clientsInfo.emplace(std::piecewise_construct, std::forward_as_tuple(clientAddress),
                                std::forward_as_tuple(clientAddress, clientPort, ClientState::InLobby));
            waitingRoom.addPlayer(clientAddress);

            sf::Packet responsePacket;
            if (waitingRoom.inGame) {
                responsePacket << static_cast<int>(PacketType::GAME);
                for (const auto &client : clientsInfo) {
                    socket.send(responsePacket, client.second.address, client.second.port);
                }
            } else {
                responsePacket << static_cast<int>(PacketType::Lobby);
                socket.send(responsePacket, clientAddress, clientPort);
            }
        }

        void handleClientDisconnection(const sf::IpAddress &clientAddress)
        {
            clientsInfo.erase(clientAddress);
            waitingRoom.removePlayer(clientAddress);
        }

        WaitingRoom                                                  waitingRoom;
        sf::UdpSocket                                                socket;
        bool                                                         isServer = true;
        bool                                                         running  = true;
        std::unordered_map<sf::IpAddress, ClientInfo, IpAddressHash> clientsInfo;
};
