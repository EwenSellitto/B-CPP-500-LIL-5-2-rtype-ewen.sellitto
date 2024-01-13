/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Booster.system.cpp
*/

#include "R-Type/Systems/Booster.system.hpp"

#include "ECS/Components.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Link.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"
#include "R-Type/Components/Booster.component.hpp"
#include "R-Type/Components/BoosterActive.component.hpp"
#include "R-Type/Components/Player.component.hpp"

using namespace Rtype::System;

void BoosterSystem::takeBooster(ECS::Entity *player, ECS::Entity *booster)
{
    using namespace Rtype::Components;

    ECS::ComponentHandle<BoosterComponent>                      boosterComponent;
    ECS::ComponentHandle<Engine::Components::PositionComponent> playerPosition;

    if (booster->has<BoosterComponent>()) boosterComponent = booster->getComponent<BoosterComponent>();
    if (player->has<Engine::Components::PositionComponent>())
        playerPosition = player->getComponent<Engine::Components::PositionComponent>();

    player->addComponent(new BoosterActiveComponent(boosterComponent->duration_seconds));
    player->addComponent(new Engine::Components::LinkComponent(player->getId()));
    WORLD.removeEntity(booster);
    WORLD.createEntity(new Engine::Components::RenderableComponent("./assets/MainShip/MainShip-Shields-RoundShield.png",
                                                                   {0, 0}, 3, 90),
                       new Engine::Components::PositionComponent(playerPosition->x + 4, playerPosition->y - 8),
                       new Engine::Components::AnimationComponent(0, 0, 64, 64, 64, 64, 100, 12),
                       new Engine::Components::LinkComponent(player->getId()), new isBoosterComponent());
}

void BoosterSystem::tick()
{
    using namespace Rtype::Components;
    using namespace Engine::Components;

    ECS::World                &world = WORLD;
    std::vector<ECS::Entity *> players =
        world.getEntitiesWithComponents<PlayerComponent, BoosterActiveComponent, LinkComponent>();
    if (players.empty()) {
        for (auto &ent : world.getEntitiesWithComponents<isBoosterComponent, LinkComponent, PositionComponent>()) {
            world.removeEntity(ent);
        }
    }
    for (auto &player : players) {
        auto boosterActive = player->getComponent<BoosterActiveComponent>();
        for (auto &ent : world.getEntitiesWithComponents<isBoosterComponent, LinkComponent, PositionComponent>()) {
            if (ent->getComponent<LinkComponent>()->entity == player->getComponent<LinkComponent>()->entity) {
                if (boosterActive->clock.getElapsedTime().asSeconds() >= boosterActive->duration ||
                    boosterActive->hitpoints <= 0) {
                    world.removeEntity(ent);
                    player->removeComponent<BoosterActiveComponent>();
                    player->removeComponent<LinkComponent>();
                    break;
                } else {
                    auto position = ent->getComponent<PositionComponent>();
                    position->x   = player->getComponent<PositionComponent>()->x + 4;
                    position->y   = player->getComponent<PositionComponent>()->y - 8;
                }
            }
        }
    }
}
