/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** MovePlayer.systems.cpp
*/

#include "Engine/Systems/MovePlayer.system.hpp"

#include <map>

#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Engine.hpp"
#include "ECS/Entity.hpp"
#include <SFML/Window/Event.hpp>

using namespace Engine::System;

void MovePlayer::configure([[maybe_unused]] ECS::World &world) {}

void MovePlayer::unconfigure() {}

void MovePlayer::addMovePlayer(sf::Event event)
{
    using namespace Engine::Components;

    if (!player)
        return;
    if (!player->has<RenderableComponent>())
        return;

    ECS::ComponentHandle<RenderableComponent> playerRenderableComp(player->getComponent<RenderableComponent>());
    std::vector<sf::Vector2f> moves_zdqs{{0, -(speed * 100)}, {speed * 100, 0}, {-(speed * 100), 0}, {0, speed * 100}};

    if (player->has<MovingComponent>()) {
        ECS::ComponentHandle<Components::MovingComponent> movingComponent(
            player->getComponent<Components::MovingComponent>());
        auto now = std::chrono::high_resolution_clock::now();
        auto epoch = now.time_since_epoch();
        size_t startTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
        movingComponent->moveStartTime = startTime;
        movingComponent->moveDuration = 1000 * 100;

        if (event.key.code == sf::Keyboard::Z)
            movingComponent->moveAmount.y += moves_zdqs[0].y;
        if (event.key.code == sf::Keyboard::D)
            movingComponent->moveAmount.x += moves_zdqs[1].x;
        if (event.key.code == sf::Keyboard::Q)
            movingComponent->moveAmount.x += moves_zdqs[2].x;
        if (event.key.code == sf::Keyboard::S)
            movingComponent->moveAmount.y += moves_zdqs[3].y;
        return;
    }
    if (event.key.code == sf::Keyboard::Z)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[0]));
    if (event.key.code == sf::Keyboard::D)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[1]));
    if (event.key.code == sf::Keyboard::Q)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[2]));
    if (event.key.code == sf::Keyboard::S)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[3]));
}

void MovePlayer::stopMovePlayer(sf::Event event)
{
    using namespace Engine::Components;

    if (!player)
        return;
    if (!player->has<RenderableComponent>())
        return;

    ECS::ComponentHandle<RenderableComponent> playerRenderableComp(player->getComponent<RenderableComponent>());
    std::vector<sf::Vector2f> moves_zdqs{{0, -(speed * 100)}, {speed * 100, 0}, {-(speed * 100), 0}, {0, speed * 100}};

    if (player->has<MovingComponent>()) {
        ECS::ComponentHandle<Components::MovingComponent> playerMovingComp(
            player->getComponent<Components::MovingComponent>());

        if (event.key.code == sf::Keyboard::Z)
            playerMovingComp->moveAmount.y -= moves_zdqs[0].y;
        if (event.key.code == sf::Keyboard::D)
            playerMovingComp->moveAmount.x -= moves_zdqs[1].x;
        if (event.key.code == sf::Keyboard::Q)
            playerMovingComp->moveAmount.x -= moves_zdqs[2].x;
        if (event.key.code == sf::Keyboard::S)
            playerMovingComp->moveAmount.y -= moves_zdqs[3].y;
        return;
    }
}

void MovePlayer::setPlayerSpeed(float newSpeed)
{
    speed = newSpeed;
}

void MovePlayer::setCurrentPlayer(ECS::Entity *entity)
{
    player = entity;
}

void MovePlayer::tick()
{
//    using namespace Engine::Components;
//
//    ECS::World                                                           &world = getWorld();
//    std::map<int, std::vector<ECS::ComponentHandle<>>> components{};
//    sf::RenderWindow                                                     *window = &WINDOW;
//    std::unordered_map<ECS::Entity *, ECS::ComponentHandle<>> ViewEntities;
//
//    world.each<>(
//        [&]([[maybe_unused]] ECS::Entity *_, ECS::ComponentHandle<> handle) {
//            components[handle->priority].push_back(handle);
//        });

}
