

#include "Engine/Systems/WaitingRoom.system.hpp"
#include "r-type.hpp"

using namespace Engine::System;

void WaitingRoom::configure([[maybe_unused]] ECS::World &world)
{
    return;
}

void WaitingRoom::unconfigure()
{
    return;
}

void WaitingRoom::tick() {}

void WaitingRoom::addPlayer(int id, std::string name)
{
    this->_players[id] = name;
}

void WaitingRoom::removePlayer(int id)
{
    this->_players.erase(id);
}

std::string WaitingRoom::getPlayers(int id)
{
    for (auto &player : this->_players) {
        std::cout << player.first << " " << player.second << std::endl;
    }
    for (auto &player : this->_players) {
        if (player.first == id) return player.second;
    }
    return "";
}
