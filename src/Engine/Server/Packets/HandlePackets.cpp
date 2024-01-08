/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** HandlePackets
*/

#include <typeindex>

#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Server/Network.hpp"

void ECS::Network::handleHandshakeRequest(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
{
    handleClientConnection(packet, sender, senderPort);
}

void ECS::Network::handleHandshakeResponse(sf::Packet &packet, const sf::IpAddress &sender, unsigned short senderPort)
{
    std::cout << "Received HandshakeResponse" << std::endl;
}

void ECS::Network::handleLeaveLobby(sf::Packet &packet, const sf::IpAddress &sender)
{
    waitingRoom.removePlayer(sender);
}

void ECS::Network::deserializeEntityAndApply(sf::Packet &packet)
{
    using namespace Engine::Components;
    int                                                    nbComponents = 0;
    std::vector<char>                                      serialised;
    int                                                    serialisedSize = 0;
    int                                                    componentType;
    sf::Uint64                                             entityId;
    std::vector<std::pair<BaseComponent *, ComponentType>> components;

    packet >> entityId;
    packet >> nbComponents;
    for (int i = 0; i < nbComponents; i++) {
        packet >> componentType;
        packet >> serialisedSize;
        if (serialisedSize > 0 && static_cast<std::size_t>(serialisedSize) <= packet.getDataSize()) {
            serialised.resize(serialisedSize);
            for (int j = 0; j < serialisedSize; ++j) {
                sf::Uint8 dataByte;
                packet >> dataByte;
                serialised[j] = static_cast<char>(dataByte);
            }
            ECS::BaseComponent *comp =
                componentsConvertor.createComponent(static_cast<ComponentType>(componentType))->deserialize(serialised);
            std::cout << "Deserialized components: " << static_cast<int>(comp->getType()) << std::endl;
            components.emplace_back(comp, componentType);
        } else {
            std::cerr << "Invalid serialized data size" << std::endl;
        }
    }
    if (Engine::EngineClass::getEngine().world().entityExists(entityId)) {
        std::vector<ComponentType> componentsToRemove;
        std::vector<ComponentType> currentEntityComponents;

        for (auto &comp : Engine::EngineClass::getEngine().world().getMutEntity(entityId).getComponents())
            currentEntityComponents.push_back(comp.second->getType());
        for (auto &comp : components) {
            for (auto &currentEntityComp : currentEntityComponents) {
                if (comp.second == currentEntityComp) {
                    componentsToRemove.push_back(currentEntityComp);
                    break;
                }
            }
        }
        for (auto &comp : componentsToRemove)
            componentsConvertor.destroyers[comp](Engine::EngineClass::getEngine().world().getMutEntity(entityId));
        for (auto &comp : components)
            componentsConvertor.adders[comp.second](Engine::EngineClass::getEngine().world().getMutEntity(entityId),
                                                    comp.first);
        return;
    }
    Engine::EngineClass::getEngine().world().addEntity(entityId);
    for (auto &comp : components)
        componentsConvertor.adders[comp.second](Engine::EngineClass::getEngine().world().getMutEntity(entityId),
                                                comp.first);
}

void ECS::Network::handleInitializeGame(sf::Packet &packet, const sf::IpAddress &sender, unsigned short clientPort)
{
    using namespace Engine::Components;

    while (packet.getDataSize() > 0) {
        deserializeEntityAndApply(packet);
    }
    sf::Packet responsePacket;
    responsePacket << static_cast<int>(PacketType::InitializeGameOkForMe);
    sendPacketToClient(responsePacket, sender, clientPort);
}

void ECS::Network::handleSwitchWorld(const sf::IpAddress &sender, unsigned short senderPort)
{
    std::cout << "Received SwitchWorld" << std::endl;
    switchToGame();
    sf::Packet responsePacket;
    responsePacket << static_cast<int>(PacketType::SwitchWorldOkForMe);
    sendPacketToClient(responsePacket, sender, senderPort);
}

void ECS::Network::handleReceiveSwitchedWorld(const sf::IpAddress &sender, unsigned short clientPort)
{
    for (const auto &player : waitingRoom.getPlayers()) {
        if (player->address == sender && player->port == clientPort) {
            player->hasSwitchedWorld = true;
            break;
        }
    }

    if (waitingRoom.allPlayersSwitchedWorld()) {
        sf::Packet packet;
        packet << static_cast<int>(PacketType::InitializeGame);
        World &world = Engine::EngineClass::getEngine().world();
        for (const auto &pair : world.getEntities())
            addSerializedEntityToPacket(packet, pair);
        sendPacketToAllClients(packet);
    }
}

void ECS::Network::addPlayerToLobby(const sf::IpAddress &clientAddress, unsigned short clientPort)
{
    World &world = Engine::EngineClass::getEngine().world();
    waitingRoom.addPlayer(clientAddress, clientPort);
    // Si tous les joueurs sont connectés, envoyer les informations du lobby
    std::cout << "Nb players: " << waitingRoom.getPlayers().size() << std::endl;
    if (waitingRoom.isReadyToStart()) {
        sf::Packet packet;
        packet << static_cast<int>(PacketType::SwitchWorld);
        sendPacketToAllClients(packet);
        // for (const auto &client : waitingRoom.getPlayers()) {
        //     sf::Packet packet;
        //     packet << static_cast<int>(PacketType::InitializeGame);
        //     for (const auto &pair : world.getEntities()) {
        //         Entity &entity = *pair.second;
        //         addSerializedEntityToPacket(packet, pair);
        //     }
        //     sendPacketToClient(packet, client.address, client.port);
        // }
    }
}