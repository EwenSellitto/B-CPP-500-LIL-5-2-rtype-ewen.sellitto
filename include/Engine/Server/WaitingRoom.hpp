#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#include "Engine/Server/ClientInfo.hpp"

struct WaitingRoom {

        void addPlayer(const sf::IpAddress &player, unsigned short port)
        {
            players.push_back(new ClientInfo(player, port, ClientState::InLobby));
        }

        std::vector<ClientInfo *> getPlayers() const
        {
            return players;
        }

        bool isReadyToStart() const
        {
            return players.size() >= 2;
        }

        bool allPlayersSwitchedWorld() const
        {
            for (const auto &player : players) {
                if (!player->hasSwitchedWorld) {
                    return false;
                }
            }
            return true;
        }

        bool allPlayersInitializedGame() const
        {
            for (const auto &player : players) {
                if (!player->isInitialized) {
                    return false;
                }
            }
            return true;
        }

        void removePlayer(const sf::IpAddress &player)
        {
            for (auto it = players.begin(); it != players.end(); it++) {
                if ((*it)->address == player) {
                    players.erase(it);
                    return;
                }
            }
        }

    private:
        std::vector<ClientInfo *> players;
};
