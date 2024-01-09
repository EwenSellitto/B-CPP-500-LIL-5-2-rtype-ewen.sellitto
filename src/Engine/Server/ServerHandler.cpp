/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ServerHandler
*/

#include "Engine/Server/Network.hpp"

void ECS::Network::startServer(unsigned short port)
{
    running  = true;
    isServer = true;
    thread   = std::thread(&Network::startClient, this, port);
}

void ECS::Network::startClient(unsigned short port)
{
    socket.setBlocking(false);
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "Erreur de liaison du port " << std::endl;
        return;
    }
    std::cout << "Client démarré sur le port " << socket.getLocalPort() << std::endl;
    addPlayerToLobby("localhost", port, isServer);
    while (running) {
        receivePackets();
    }
    socket.unbind();
}

void ECS::Network::connectToServer(const sf::IpAddress &serverAddress, unsigned short port)
{
    thread   = std::thread(&Network::sendConnectionToServer, this, serverAddress, port);
    isServer = false;
}

void ECS::Network::sendConnectionToServer(const sf::IpAddress &serverAddress, unsigned short port)
{
    sf::Packet packet;
    packet << static_cast<int>(PacketType::HandshakeRequest);
    packet << false;
    serverHost = std::make_pair(serverAddress, port);
    std::cout << "Demande de connexion au serveur " << serverAddress << ":" << port << std::endl;
    socket.setBlocking(false);
    if (socket.send(packet, serverAddress, port) != sf::Socket::Done) {
        std::cerr << "Erreur lors de l'envoi de la demande de connexion" << std::endl;
    }
    receivePackets();
}

void ECS::Network::stop()
{
    running = false;
    if (thread.joinable()) thread.join();
}