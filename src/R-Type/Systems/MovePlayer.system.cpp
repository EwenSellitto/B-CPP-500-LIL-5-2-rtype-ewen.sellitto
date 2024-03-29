/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** MovePlayer.systems.cpp
*/

#include "R-Type/Systems/MovePlayer.system.hpp"

#include <SFML/Window/Event.hpp>

#include "ECS/Entity.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Engine.hpp"
#include "R-Type/Components/Player.component.hpp"

using namespace Engine::System;

void MovePlayer::configure([[maybe_unused]] ECS::World &world) {}

void MovePlayer::unconfigure() {}

void MovePlayer::addMovePlayer(sf::Event::KeyEvent key)
{
    using namespace Engine::Components;

    std::vector<ECS::Entity *> players = WORLD.getEntitiesWithComponents<PlayerComponent>();
    ECS::Entity               *player  = nullptr;

    for (auto &p : players) {
        if (p->getComponent<PlayerComponent>()->playerNb == EngineClass::getEngine().getCurrentPlayer()) {
            player = p;
            break;
        }
    }

    if (!player) {
        return;
    }

    if (!player->has<SpeedComponent>() || !player->has<PositionComponent>()) {
        return;
    }
    ECS::ComponentHandle<SpeedComponent> speedComponent = player->getComponent<SpeedComponent>();
    float                                speed          = speedComponent->speed;

    ECS::ComponentHandle<PositionComponent> playerPos(player->getComponent<PositionComponent>());
    std::vector<sf::Vector2f> moves_zdqs{{0, -(speed)*100}, {speed * 100, 0}, {-(speed)*100, 0}, {0, speed * 100}};

    if (player->has<MovingComponent>()) {
        ECS::ComponentHandle<Components::MovingComponent> movingComponent(
            player->getComponent<Components::MovingComponent>(true));

        if ((movingComponent->moveAmount.y == moves_zdqs[0].y || movingComponent->moveAmount.y == moves_zdqs[3].y) &&
            (key.code == sf::Keyboard::Z || key.code == sf::Keyboard::S))
            return;
        if ((movingComponent->moveAmount.x == moves_zdqs[1].x || movingComponent->moveAmount.x == moves_zdqs[2].x) &&
            (key.code == sf::Keyboard::D || key.code == sf::Keyboard::Q))
            return;

        sf::Vector2f movingValuesSave = movingComponent->moveAmount;
        player->removeComponent<MovingComponent>(true);

        switch (key.code) {
            case sf::Keyboard::Z:
                movingValuesSave.y = moves_zdqs[0].y;
                break;
            case sf::Keyboard::D:
                movingValuesSave.x = moves_zdqs[1].x;
                break;
            case sf::Keyboard::Q:
                movingValuesSave.x = moves_zdqs[2].x;
                break;
            case sf::Keyboard::S:
                movingValuesSave.y = moves_zdqs[3].y;
                break;
            default:
                break;
        }
        player->addComponent(new MovingComponent({static_cast<float>(playerPos->x), static_cast<float>(playerPos->y)},
                                                 1000 * 100, movingValuesSave));
        return;
    }

    switch (key.code) {
        case sf::Keyboard::Z:
            player->addComponent(new MovingComponent(
                {static_cast<float>(playerPos->x), static_cast<float>(playerPos->y)}, 1000 * 100, moves_zdqs[0]));
            break;
        case sf::Keyboard::D:
            player->addComponent(new MovingComponent(
                {static_cast<float>(playerPos->x), static_cast<float>(playerPos->y)}, 1000 * 100, moves_zdqs[1]));
            break;
        case sf::Keyboard::Q:
            player->addComponent(new MovingComponent(
                {static_cast<float>(playerPos->x), static_cast<float>(playerPos->y)}, 1000 * 100, moves_zdqs[2]));
            break;
        case sf::Keyboard::S:
            player->addComponent(new MovingComponent(
                {static_cast<float>(playerPos->x), static_cast<float>(playerPos->y)}, 1000 * 100, moves_zdqs[3]));
            break;
        default:
            break;
    }
}

void MovePlayer::stopMovePlayer(sf::Event::KeyEvent key)
{
    using namespace Engine::Components;

    std::vector<ECS::Entity *> players =
        Engine::EngineClass::getEngine().world().getEntitiesWithComponents<PlayerComponent>();
    ECS::Entity *player = nullptr;

    for (auto &p : players) {
        if (p->getComponent<PlayerComponent>()->playerNb == Engine::EngineClass::getEngine().getCurrentPlayer()) {
            player = p;
            break;
        }
    }

    if (!player) return;

    if (!player->has<SpeedComponent>() || !player->has<PositionComponent>()) return;
    ECS::ComponentHandle<SpeedComponent> speedComponent = player->getComponent<SpeedComponent>();
    float                                speed          = speedComponent->speed;

    ECS::ComponentHandle<PositionComponent> playerPos(player->getComponent<PositionComponent>());
    std::vector<sf::Vector2f> moves_zdqs{{0, -(speed)*100}, {speed * 100, 0}, {-(speed)*100, 0}, {0, speed * 100}};

    if (player->has<MovingComponent>()) {
        ECS::ComponentHandle<Components::MovingComponent> playerMovingComp(
            player->getComponent<Components::MovingComponent>(true));

        sf::Vector2f movingValuesSave = playerMovingComp->moveAmount;
        player->removeComponent<MovingComponent>(true);

        if (key.code == sf::Keyboard::Z || key.code == sf::Keyboard::S) movingValuesSave.y = 0;
        if (key.code == sf::Keyboard::D || key.code == sf::Keyboard::Q) movingValuesSave.x = 0;
        if (movingValuesSave.x == 0 && movingValuesSave.y == 0) return;
        player->addComponent(new MovingComponent({static_cast<float>(playerPos->x), static_cast<float>(playerPos->y)},
                                                 1000 * 100, movingValuesSave));
    }
}

void MovePlayer::tick() {}
