/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Physics.systems.cpp
*/

#include "Engine/Systems/Physics.system.hpp"

#include <map>

#include "ECS/Entity.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/Player.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void Physics::configure([[maybe_unused]] ECS::World &world) {}

void Physics::unconfigure() {}

void Physics::collide()
{

}

void Physics::moveTime(ECS::Entity *entity, ECS::ComponentHandle<Components::MovingComponent> handle)
{
    auto now = std::chrono::high_resolution_clock::now();
    auto epoch = now.time_since_epoch();
    size_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

    size_t moveStartTime = handle->moveStartTime;
    size_t moveDuration = handle->moveDuration;
    sf::Vector2f initialPos = handle->initialPos;
    sf::Vector2f moveAmount = handle->moveAmount;

    size_t elapsedTime = currentTime - moveStartTime;
    double progress = std::min(static_cast<double>(elapsedTime) / static_cast<double>(moveDuration), 1.0);
    sf::Vector2f newPosition = initialPos + moveAmount * static_cast<float>(progress);

    int endedMoveCounter = 0;

    if (moveAmount.x > 0 && newPosition.x >= initialPos.x + moveAmount.x) {
        newPosition.x = initialPos.x + moveAmount.x;
        endedMoveCounter++;
    }
    if (moveAmount.y > 0 && newPosition.y >= initialPos.y + moveAmount.y) {
        newPosition.y = initialPos.y + moveAmount.y;
        endedMoveCounter++;
    }
    if (moveAmount.x < 0 && newPosition.x <= initialPos.x + moveAmount.x) {
        newPosition.x = initialPos.x + moveAmount.x;
        endedMoveCounter++;
    }
    if (moveAmount.y < 0 && newPosition.y <= initialPos.y + moveAmount.y) {
        newPosition.y = initialPos.y + moveAmount.y;
        endedMoveCounter++;
    }
    if (!entity->has<Components::RenderableComponent>())
        return;
    ECS::ComponentHandle<Components::RenderableComponent> renderableComponent(
        entity->getComponent<Components::RenderableComponent>());

    //TODO : insert the collide function.

    renderableComponent->position = newPosition;
    renderableComponent->sprite.setPosition(newPosition);
    if (endedMoveCounter == 2)
        entity->removeComponent<Components::MovingComponent>();
}

void Physics::tick()
{
    using namespace Engine::Components;

    ECS::World                                                           &world = getWorld();

    world.each<MovingComponent>(
        [&](ECS::Entity *entity, ECS::ComponentHandle<MovingComponent> handle) {
            moveTime(entity, handle);
        });
}
