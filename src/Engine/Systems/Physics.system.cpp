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
#include "Engine/Components/Player.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Events/Collision.event.hpp"

using namespace Engine::System;

void Physics::configure([[maybe_unused]] ECS::World &world) {}

void Physics::unconfigure() {}

void Physics::collide(ECS::Entity *entity)
{
    using namespace Engine::Components;

    ECS::World                &world = getWorld();
    std::vector<ECS::Entity *> collisionEntities;

    if (!entity->has<CollisionComponent>() || !entity->has<RenderableComponent>()) return;
    ECS::ComponentHandle<RenderableComponent> entityRenderableComp = entity->getComponent<RenderableComponent>();

    world.each<CollisionComponent>([&]([[maybe_unused]] ECS::Entity                                    *currentEntity,
                                       [[maybe_unused]] const ECS::ComponentHandle<CollisionComponent> &handle) {
        if (currentEntity != entity && currentEntity->has<RenderableComponent>()) {
            ECS::ComponentHandle<RenderableComponent> currentEntityRenderableComp =
                currentEntity->getComponent<RenderableComponent>();
            if (entityRenderableComp->sprite.getGlobalBounds().intersects(
                    currentEntityRenderableComp->sprite.getGlobalBounds()))
                collisionEntities.push_back(currentEntity);
        }
    });
    if (collisionEntities.empty()) return;
    for (auto &collisionEntity : collisionEntities)
        world.broadcastEvent<CollisionEvent>({entity, collisionEntity});
}

void Physics::moveTime(ECS::Entity *entity, ECS::ComponentHandle<Components::MovingComponent> handle)
{
    using namespace Engine::Components;

    auto   now         = std::chrono::high_resolution_clock::now();
    auto   epoch       = now.time_since_epoch();
    size_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

    size_t       moveStartTime = handle->moveStartTime;
    size_t       moveDuration  = handle->moveDuration;
    sf::Vector2f initialPos    = handle->initialPos;
    sf::Vector2f moveAmount    = handle->moveAmount;

    size_t       elapsedTime = currentTime - moveStartTime;
    double       progress    = std::min(static_cast<double>(elapsedTime) / static_cast<double>(moveDuration), 1.0);
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
    if (!entity->has<PositionComponent>() || !entity->has<RenderableComponent>()) return;
    ECS::ComponentHandle<PositionComponent> componentPos(entity->getComponent<PositionComponent>());
    ECS::ComponentHandle<RenderableComponent> renderableComponent(entity->getComponent<RenderableComponent>());

    collide(entity);

    componentPos->x = static_cast<int>(newPosition.x);
    componentPos->y = static_cast<int>(newPosition.y);
    renderableComponent->sprite.setPosition(newPosition);
    if (endedMoveCounter == 2) entity->removeComponent<MovingComponent>();
}

void Physics::tick()
{
    using namespace Engine::Components;

    ECS::World &world = getWorld();

    world.each<MovingComponent>(
        [&](ECS::Entity *entity, ECS::ComponentHandle<MovingComponent> handle) { moveTime(entity, handle); });
}
