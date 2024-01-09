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
            std::cout << "Deserialized components: " << static_cast<int>(comp->getType()) << std::endl;
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
        for (auto &comp : componentsToRemove)
            componentsConvertor.destroyers[comp](Engine::EngineClass::getEngine().world().getMutEntity(entityId));
        for (auto &component : components) {
            if (component.second == ComponentType::RenderableComponent)
                dynamic_cast<RenderableComponent *>(component.first)->setTexture();
            componentsConvertor.adders[component.second](
                Engine::EngineClass::getEngine().world().getMutEntity(entityId), component.first);
        }
        return;
    }
    std::cout << "entityId " << entityId << std::endl;
    Engine::EngineClass::getEngine().world().addEntity(entityId);
    std::cout << "nextId " << Utils::getNewId<Entity>() << std::endl;
    for (auto &comp : components) {
        componentsConvertor.adders[comp.second](Engine::EngineClass::getEngine().world().getMutEntity(entityId),
                                                comp.first);
        if (comp.second == ComponentType::RenderableComponent)
            dynamic_cast<RenderableComponent *>(comp.first)->setTexture();
    }
}