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

void MovePlayer::addMovePlayer(sf::Event::KeyEvent key)
{
    using namespace Engine::Components;

    if (!player)
        return;
    if (!player->has<RenderableComponent>())
        return;

    ECS::ComponentHandle<RenderableComponent> playerRenderableComp(player->getComponent<RenderableComponent>());
    std::vector<sf::Vector2f> moves_zdqs{{0, -(speed) * 100}, {speed * 100, 0}, {-(speed) * 100, 0}, {0, speed * 100}};

    if (player->has<MovingComponent>()) {
        ECS::ComponentHandle<Components::MovingComponent> movingComponent(
            player->getComponent<Components::MovingComponent>());

        if ((movingComponent->moveAmount.y == moves_zdqs[0].y ||
            movingComponent->moveAmount.y == moves_zdqs[3].y) &&
            (key.code == sf::Keyboard::Z || key.code == sf::Keyboard::S))
            return;
        if ((movingComponent->moveAmount.x == moves_zdqs[1].x ||
            movingComponent->moveAmount.x == moves_zdqs[2].x) &&
            (key.code == sf::Keyboard::D || key.code == sf::Keyboard::Q))
            return;

        sf::Vector2f movingValuesSave = movingComponent->moveAmount;
        player->removeComponent<MovingComponent>();

        if (key.code == sf::Keyboard::Z)
            movingValuesSave.y = moves_zdqs[0].y;
        if (key.code == sf::Keyboard::D)
            movingValuesSave.x = moves_zdqs[1].x;
        if (key.code == sf::Keyboard::Q)
            movingValuesSave.x = moves_zdqs[2].x;
        if (key.code == sf::Keyboard::S)
            movingValuesSave.y = moves_zdqs[3].y;
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, movingValuesSave));
        return;
    }
    if (key.code == sf::Keyboard::Z)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[0]));
    if (key.code == sf::Keyboard::D)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[1]));
    if (key.code == sf::Keyboard::Q)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[2]));
    if (key.code == sf::Keyboard::S)
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, moves_zdqs[3]));
}

void MovePlayer::stopMovePlayer(sf::Event::KeyEvent key)
{
    using namespace Engine::Components;

    if (!player)
        return;
    if (!player->has<RenderableComponent>())
        return;

    ECS::ComponentHandle<RenderableComponent> playerRenderableComp(player->getComponent<RenderableComponent>());
    std::vector<sf::Vector2f> moves_zdqs{{0, -(speed) * 100}, {speed * 100, 0}, {-(speed) * 100, 0}, {0, speed * 100}};

    if (player->has<MovingComponent>()) {
        ECS::ComponentHandle<Components::MovingComponent> playerMovingComp(
            player->getComponent<Components::MovingComponent>());

        sf::Vector2f movingValuesSave = playerMovingComp->moveAmount;
        player->removeComponent<MovingComponent>();

        if (key.code == sf::Keyboard::Z || key.code == sf::Keyboard::S)
            movingValuesSave.y = 0;
        if (key.code == sf::Keyboard::D || key.code == sf::Keyboard::Q)
            movingValuesSave.x = 0;
        if (movingValuesSave.x == 0 && movingValuesSave.y == 0)
            return;
        player->addComponent(new MovingComponent(playerRenderableComp->position, 1000 * 100, movingValuesSave));
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
