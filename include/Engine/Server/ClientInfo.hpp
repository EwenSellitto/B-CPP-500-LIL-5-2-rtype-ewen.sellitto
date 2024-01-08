#include <SFML/Network.hpp>
#include <iostream>

enum class ClientState {
    InLobby,
    InGame,
    Disconnected
};

struct ClientInfo {
        sf::IpAddress  address;
        unsigned short port;
        ClientState    state;
        bool           hasSwitchedWorld = false;
        bool           isInitialized    = false;

        ClientInfo() : port(0), state(ClientState::Disconnected) {} // Constructeur par défaut

        ClientInfo(const sf::IpAddress &addr, unsigned short prt, ClientState st) : address(addr), port(prt), state(st)
        {
        }
};
