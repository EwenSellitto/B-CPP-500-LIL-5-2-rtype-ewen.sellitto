#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#include "Engine/Server/ClientInfo.hpp"

struct WaitingRoom {

        void addPlayer(const sf::IpAddress &player, unsigned short port)
        {
            players.push_back(ClientInfo(player, port, ClientState::InLobby));
        }

        std::vector<ClientInfo> getPlayers() const
        {
            return players;
        }

        bool isReadyToStart() const
        {
            return players.size() >= 2;
        }

        void removePlayer(const sf::IpAddress &player)
        {
            for (auto it = players.begin(); it != players.end(); it++) {
                if (it->address == player) {
                    players.erase(it);
                    return;
                }
            }
        }

    private:
        std::vector<ClientInfo> players;
};
