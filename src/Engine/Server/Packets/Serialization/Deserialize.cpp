/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Deserialize
*/

#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Server/Network.hpp"

sf::Event ECS::Network::deserializeEvent(sf::Packet &packet)
{
    sf::Event event;
    sf::Int32 eventType;
    packet >> eventType;
    event.type = static_cast<sf::Event::EventType>(eventType);
    int temp   = 0;

    switch (event.type) {
        case sf::Event::KeyPressed:
        case sf::Event::KeyReleased: // KeyPressed et KeyReleased ont la même structure
            packet >> temp;
            event.key.code = static_cast<sf::Keyboard::Key>(temp);
            packet >> temp;
            event.key.alt = static_cast<bool>(temp);
            packet >> temp;
            event.key.control = static_cast<bool>(temp);
            packet >> temp;
            event.key.shift = static_cast<bool>(temp);
            packet >> temp;
            event.key.system = static_cast<bool>(temp);
            break;
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased: // MouseButtonPressed et MouseButtonReleased ont la même structure
            packet >> temp;
            event.mouseButton.button = static_cast<sf::Mouse::Button>(temp);
            packet >> event.mouseButton.x;
            packet >> event.mouseButton.y;
            break;
        case sf::Event::MouseMoved:
            packet >> event.mouseMove.x;
            packet >> event.mouseMove.y;
            break;
        case sf::Event::MouseWheelScrolled:
            packet >> temp;
            event.mouseWheelScroll.wheel = static_cast<sf::Mouse::Wheel>(temp);
            packet >> event.mouseWheelScroll.delta;
            packet >> event.mouseWheelScroll.x;
            packet >> event.mouseWheelScroll.y;
            break;
    }

    return event;
}

void ECS::Network::deserializeRemoveEntitiesAndRemove(sf::Packet &packet)
{
    sf::Uint64 entityId;

    packet >> entityId;
    if (WORLD.entityExists(entityId)) {
        std::cout << "REMOVED ENTITY " << std::endl;
        componentsToUpdate.emplace_back(static_cast<ECS::id_t>(entityId), std::vector<ComponentType>(),
                                        std::vector<std::pair<BaseComponent *, ComponentType>>());
    } else {
        std::cout << "nto removed entity" << std::endl;
    }
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
        if (serialisedSize >= 0 && static_cast<std::size_t>(serialisedSize) <= packet.getDataSize()) {
            serialised.resize(serialisedSize);
            for (int j = 0; j < serialisedSize; ++j) {
                sf::Uint8 dataByte;
                packet >> dataByte;
                serialised[j] = static_cast<char>(dataByte);
            }
            ECS::BaseComponent *comp =
                componentsConvertor.createComponent(static_cast<ComponentType>(componentType))->deserialize(serialised);
            components.emplace_back(comp, static_cast<ComponentType>(componentType));
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
        std::cout << "deserializeEntityAndApply SI CA EXISTE" << std::endl;
        if (components.empty()) {
            std::cout << "CA FONCTIONNE PAS -> componentsToRemove ou components est vide " << std::endl;
            return;
        } else
            componentsToUpdate.emplace_back(entityId, componentsToRemove, components);
        std::cout << "TOUT EST GOOD" << std::endl;
        return;
    }
    std::cout << "deserializeEntityAndApply" << std::endl;
    if (components.empty()) {
        std::cout << "CA FONCTIONNE PAS -> components est vide " << std::endl;
        return;
    } else
        std::cout << "TOUT EST GOOD" << std::endl;
    componentsToUpdate.emplace_back(entityId, std::vector<ComponentType>(), components);
}

void ECS::Network::deserializeRemovedComponentsAndApply(sf::Packet &packet)
{
    using namespace Engine::Components;
    int                        nbComponents = 0;
    int                        componentType;
    sf::Uint64                 entityId;
    std::vector<ComponentType> componentsToRemove;

    packet >> entityId;
    packet >> nbComponents;
    for (int i = 0; i < nbComponents; i++) {
        packet >> componentType;
        if (!WORLD.entityExists(entityId)) continue;
        ECS::Entity &entity = Engine::EngineClass::getEngine().world().getMutEntity(entityId);
        for (auto &comp : entity.getComponents()) {
            if (comp.second->getType() == static_cast<ComponentType>(componentType)) {
                componentsToRemove.push_back(static_cast<ComponentType>(componentType));
                break;
            }
        }
    }
    std::cout << "deserializeRemovedComponentsAndApply" << std::endl;
    if (componentsToRemove.empty()) {
        std::cout << "CA FONCTIONNE PAS -> componentsToRemove est vide " << std::endl;
        return;
    } else
        std::cout << "TOUT EST GOOD" << std::endl;

    componentsToUpdate.emplace_back(entityId, componentsToRemove,
                                    std::vector<std::pair<BaseComponent *, ComponentType>>());
}