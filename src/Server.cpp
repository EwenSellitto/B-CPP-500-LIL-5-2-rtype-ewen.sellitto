#include "Server/Server.hpp"
#include <iostream>

#include <chrono>
#include <thread>

Server::Server(unsigned short port) : port(port) {
    if (socket.bind(port) != sf::Socket::Done) {
        std::cerr << "Erreur de liaison du port " << port << std::endl;
        exit(1); // ou gérer l'erreur d'une manière appropriée
    }

    socket.setBlocking(false);  // Réglez le socket en mode non-bloquant
}

void Server::run() {
    while (running) {
        receivePackets();
        sendUpdates();
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Pause pour limiter la charge CPU
    }
}

void Server::receivePackets() {
    sf::IpAddress sender;
    unsigned short port;
    std::vector<char> packet(1024);
    std::size_t received;

    while (socket.receive(packet.data(), packet.size(), received, sender, port) == sf::Socket::Done) {
        packet.resize(received);
        std::cout << "Received packet from " << sender << ":" << port << std::endl;
        std::cout << "Packet contents: " << std::string(packet.begin(), packet.end()) << std::endl;
        processPacket(sender, port, packet);
    }
}

void Server::processPacket(const sf::IpAddress& sender, unsigned short port, const std::vector<char>& packet) {
    // Traiter le paquet reçu
    // Par exemple, enregistrer un nouveau client ou mettre à jour les données d'un client existant
    clients[sender] = port;

    // TODO: Ajouter plus de logique ici pour gérer différents types de paquets
}

void Server::sendUpdates() {
    // Envoyer des mises à jour à tous les clients
    for (const auto& client : clients) {
        std::vector<char> updatePacket; // Construire le paquet de mise à jour
        // TODO: Remplir updatePacket avec les données de mise à jour

        socket.send(updatePacket.data(), updatePacket.size(), client.first, client.second);
    }
}
