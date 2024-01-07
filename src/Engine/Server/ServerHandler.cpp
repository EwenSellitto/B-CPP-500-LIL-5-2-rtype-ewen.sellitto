/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ServerHandler
*/

#include "Engine/Server/Network.hpp"

void ECS::Network::startServer(unsigned short port)
{
    running = true;
    thread  = std::thread(&Network::startClient, this, port);
    std::thread updateThread(&Network::startServerUpdateLoop, this);
    updateThread.detach(); // Vous pouvez également conserver le thread pour le rejoindre plus tard
}

void ECS::Network::startClient(unsigned short port)
{
    socket.setBlocking(false);
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "Erreur de liaison du port " << std::endl;
        return;
    }
    std::cout << "Client démarré sur le port " << socket.getLocalPort() << std::endl;
    addPlayerToLobby("localhost", port);
    while (running) {
        receivePackets();
    }
    socket.unbind();
}

void ECS::Network::startServerUpdateLoop()
{
    while (running) {
        sendComponentsUpdate();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void ECS::Network::connectToServer(const sf::IpAddress &serverAddress, unsigned short port)
{
    thread = std::thread(&Network::sendConnectionToServer, this, serverAddress, port);
}

void ECS::Network::sendConnectionToServer(const sf::IpAddress &serverAddress, unsigned short port)
{
    sf::Packet packet;
    packet << static_cast<int>(
        PacketType::HandshakeRequest); // Envoi de la requête de handshake avec la version du client
    std::cout << "Demande de connexion au serveur " << serverAddress << ":" << port << std::endl;
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