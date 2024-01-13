#include <SFML/Network.hpp>
#include <iostream>
#include <vector>

#include "Engine/Server/ClientInfo.hpp"

struct WaitingRoom {

        void addPlayer(const sf::IpAddress &player, unsigned short port, bool isServer = false)
        {
            players.push_back(new ClientInfo(player, port, ClientState::InLobby, isServer));
        }

        std::vector<ClientInfo *> getPlayers() const
        {
            return players;
        }

        bool isGameStarted() const
        {
            return isStarted;
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

        bool allPlayersInitializedGame()
        {
            for (const auto &player : players) {
                if (!player->isInitialized) {
                    return false;
                }
            }
            isStarted = true;
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

        std::vector<ClientInfo *> getPlayers()
        {
            return players;
        }

    private:
        std::vector<ClientInfo *> players;
        bool                      isStarted = false;
};
