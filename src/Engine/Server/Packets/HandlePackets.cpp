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
#include "R-Type/GameWorld/GameWorld.hpp"

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
        std::cout << "Serialised size: " << serialisedSize << std::endl;
        if (serialisedSize >= 0 && static_cast<std::size_t>(serialisedSize) <= packet.getDataSize()) {
            serialised.resize(serialisedSize);
            for (int j = 0; j < serialisedSize; ++j) {
                sf::Uint8 dataByte;
                packet >> dataByte;
                serialised[j] = static_cast<char>(dataByte);
            }
            ECS::BaseComponent *comp =
                componentsConvertor.createComponent(static_cast<ComponentType>(componentType))->deserialize(serialised);
            std::cout << "Deserialized components: " << static_cast<int>(comp->getType()) << std::endl;
            components.emplace_back(comp, static_cast<ComponentType>(componentType));
        } else {
            std::cerr << serialisedSize << " " << static_cast<std::size_t>(serialisedSize) << " "
                      << packet.getDataSize() << std::endl;
            std::cerr << "Invalid serialized data size" << std::endl;
        }
    }
    std::cout << "Len components: " << components.size() << std::endl;
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
        for (auto &component : components)
            componentsConvertor.adders[component.second](
                Engine::EngineClass::getEngine().world().getMutEntity(entityId), component.first);

        if (Engine::EngineClass::getEngine().world().getMutEntity(entityId).has<RenderableComponent>())
            Engine::EngineClass::getEngine()
                .world()
                .getMutEntity(entityId)
                .getComponent<RenderableComponent>()
                ->setTexture();
        return;
    }
    Engine::EngineClass::getEngine().world().addEntity(entityId);
    for (auto &comp : components)
        componentsConvertor.adders[comp.second](Engine::EngineClass::getEngine().world().getMutEntity(entityId),
                                                comp.first);
    if (Engine::EngineClass::getEngine().world().getMutEntity(entityId).has<RenderableComponent>())
        Engine::EngineClass::getEngine()
            .world()
            .getMutEntity(entityId)
            .getComponent<RenderableComponent>()
            ->setTexture();
}

void ECS::Network::handleInitializeGame(sf::Packet &packet, const sf::IpAddress &sender, unsigned short clientPort)
{
    using namespace Engine::Components;
    int nbEntities = 0;

    packet >> nbEntities;
    for (int i = 0; i < nbEntities; i++) {
        deserializeEntityAndApply(packet);
    }
    sf::Packet responsePacket;
    responsePacket << static_cast<int>(PacketType::InitializeGameOkForMe);
    sendPacketToClient(responsePacket, sender, clientPort);
}

void ECS::Network::handleReceiveInitializedGame(const sf::IpAddress &sender, unsigned short clientPort)
{
    for (const auto &player : waitingRoom.getPlayers()) {
        if (player->address == sender && player->port == clientPort) {
            player->isInitialized = true;
            break;
        }
    }

    if (waitingRoom.allPlayersInitializedGame()) {
        sf::Packet packet;
        packet << static_cast<int>(PacketType::LaunchGame);
        sendPacketToAllClients(packet);
    }
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
        GameWorld::addToGameWorldServerSide(&world);
        int nbEntities = 0;
        for (const auto &pair : world.getEntities()) {
            for (const auto &component : pair.second->getComponents()) {
                if (component.second->getType() != ComponentType::NoneComponent && component.second->hasChanged()) {
                    nbEntities++;
                    break;
                }
            }
        }
        packet << nbEntities;
        for (const auto &pair : world.getEntities())
            addSerializedEntityToPacket(packet, pair);
        std::cout << "Size restant: " << packet.getDataSize() << std::endl;
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