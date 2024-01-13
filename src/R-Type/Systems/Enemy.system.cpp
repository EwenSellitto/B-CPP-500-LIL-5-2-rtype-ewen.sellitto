/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "R-Type/Systems/Enemy.system.hpp"

#include <cmath>

#include "ECS/Components.hpp"
#include "ECS/World.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Moving.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "Engine/Engine.hpp"
#include "Engine/Utils/Math.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/Systems/Bullets.system.hpp"
#include "SFML/System/Vector2.hpp"

using namespace Engine::System;

void EnemySystem::configure([[maybe_unused]] ECS::World &world) {}

void EnemySystem::unconfigure() {}

void EnemySystem::trySpawnEnemies()
{
    using namespace Engine::Components;

    ECS::World  &world         = WORLD;
    ECS::Entity *enemyQueue    = world.getEntityWithComponents<EnemyQueueComponent>();
    ECS::Entity *worldProgress = world.getEntityWithComponents<WorldMoveProgressComponent>();

    if (!enemyQueue || !worldProgress) return;
    for (auto &element : enemyQueue->getComponent<EnemyQueueComponent>()->newEnemyQueueFactories) {
        if (element.first) continue;
        if (std::get<0>(element.second.first) > worldProgress->getComponent<WorldMoveProgressComponent>()->progress)
            continue;
        element.first  = true;
        size_t enemyId = element.second.second(std::get<1>(element.second.first), std::get<2>(element.second.first),
                                               std::get<3>(element.second.first));
        ECS::Entity &currentEnemy = world.getMutEntity(enemyId);
        if (!currentEnemy.has<PositionComponent>() || !currentEnemy.has<EnemyMovementsComponent>()) return;
        currentEnemy.addComponent<MovingComponent>(
            new MovingComponent(sf::Vector2f{static_cast<float>(currentEnemy.getComponent<PositionComponent>()->x),
                                             static_cast<float>(currentEnemy.getComponent<PositionComponent>()->y)},
                                currentEnemy.getComponent<EnemyMovementsComponent>()->movementsQueueLoop[0].first,
                                currentEnemy.getComponent<EnemyMovementsComponent>()->movementsQueueLoop[0].second));
    }
}

void EnemySystem::tryChangeEnemiesMovement()
{
    using namespace Engine::Components;
    ECS::World &world = WORLD;

    std::vector<ECS::Entity *> enemies = world.getEntitiesWithComponents<RenderableComponent, EnemyComponent>();

    if (enemies.empty()) return;

    for (auto &currentEnemy : enemies) {
        if (!currentEnemy->has<PositionComponent>() || !currentEnemy->has<EnemyMovementsComponent>() ||
            currentEnemy->has<MovingComponent>())
            continue;
        size_t movementToAdd = currentEnemy->getComponent<EnemyMovementsComponent>()->currentMove + 1;
        if (movementToAdd >= currentEnemy->getComponent<EnemyMovementsComponent>()->movementsQueueLoop.size())
            movementToAdd = 0;
        currentEnemy->getComponent<EnemyMovementsComponent>()->currentMove = movementToAdd;
        currentEnemy->addComponent(new MovingComponent(
            sf::Vector2f{static_cast<float>(currentEnemy->getComponent<PositionComponent>()->x),
                         static_cast<float>(currentEnemy->getComponent<PositionComponent>()->y)},
            currentEnemy->getComponent<EnemyMovementsComponent>()->movementsQueueLoop[movementToAdd].first,
            currentEnemy->getComponent<EnemyMovementsComponent>()->movementsQueueLoop[movementToAdd].second));
    }
}

sf::Vector2f getBulletDestination(sf::Vector2f &playerPos, sf::Vector2f &enemyPos)
{
    const int screenWidth  = WINDOW.getSize().x;
    const int screenHeight = WINDOW.getSize().y;

    const int offset = 100;

    sf::Vector2<float> enemyPosVector = {static_cast<float>(enemyPos.x), static_cast<float>(enemyPos.y)};

    sf::Vector2<float> direction           = playerPos - enemyPosVector;
    float              magnitude           = sqrt(direction.x * direction.x + direction.y * direction.y);
    sf::Vector2<float> normalizedDirection = {direction.x / magnitude, direction.y / magnitude};

    sf::Vector2<float> horizontalIntersection =
        enemyPosVector +
        normalizedDirection * ((enemyPosVector.y < playerPos.y ? screenHeight + offset : -offset - enemyPosVector.y) /
                               normalizedDirection.y);
    sf::Vector2<float> verticalIntersection =
        enemyPosVector +
        normalizedDirection * ((enemyPosVector.x < playerPos.x ? screenWidth + offset : -offset - enemyPosVector.x) /
                               normalizedDirection.x);

    sf::Vector2<float> intersection;
    if ((horizontalIntersection.x >= -offset && horizontalIntersection.x <= screenWidth + offset) &&
        (horizontalIntersection.y >= -offset && horizontalIntersection.y <= screenHeight + offset)) {
        intersection = horizontalIntersection;
    } else {
        intersection = verticalIntersection;
    }

    sf::Vector2<float> extendedPoint = intersection + normalizedDirection * 100.0f;

    if (extendedPoint.x <= 1000 && extendedPoint.y <= 1000) {
        float scaleFactor =
            std::max((1000 - intersection.x) / normalizedDirection.x, (1000 - intersection.y) / normalizedDirection.y);

        extendedPoint = intersection + normalizedDirection * scaleFactor;
    }

    return extendedPoint;
}

void EnemySystem::tryMakeEnemyAttack()
{
    using namespace Engine::Components;

    ECS::World                &world = WORLD;
    std::vector<ECS::Entity *> enemies =
        world.getEntitiesWithComponents<RenderableComponent, EnemyComponent, EnemyAttackComponent, PositionComponent>();

    if (enemies.empty()) return;
    auto player = WORLD.getEntityWithComponents<PositionComponent, PlayerComponent>();
    if (!player) return;

    auto   now                = std::chrono::high_resolution_clock::now();
    auto   epoch              = now.time_since_epoch();
    size_t currentTime        = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();
    auto   playerPosComponent = player->getComponent<PositionComponent>();

    for (auto &currentEnemy : enemies) {
        ECS::ComponentHandle<EnemyAttackComponent> comp = currentEnemy->getComponent<EnemyAttackComponent>();
        if (currentTime - comp->lastAttack < comp->attackRate) continue;

        auto               enemyPosComponent = currentEnemy->getComponent<PositionComponent>();
        sf::Vector2<float> enemyPos          = {static_cast<float>(enemyPosComponent->x),
                                                static_cast<float>(enemyPosComponent->y)};
        sf::Vector2<float> playerPos         = {static_cast<float>(playerPosComponent->x),
                                                static_cast<float>(playerPosComponent->y)};

        comp->bulletDestination = getBulletDestination(playerPos, enemyPos);

        comp->lastAttack = currentTime;

        float angleRadians = std::atan2(comp->bulletDestination.y, comp->bulletDestination.x);
        float angle        = angleRadians * 180.0f / static_cast<float>(PI);
        angle += 90.0f;
        if (angle < 0) angle += 360.0f;

        Engine::System::Bullets *bulletsSystem = dynamic_cast<Engine::System::Bullets *>(
            Engine::EngineClass::getEngine().world().getSystems()["BulletsSystem"].get());
        if (!bulletsSystem) return;
        bulletsSystem->spawnBullet(true, static_cast<float>(currentEnemy->getComponent<PositionComponent>()->x),
                                   static_cast<float>(currentEnemy->getComponent<PositionComponent>()->y),
                                   comp->bulletDestination, comp->bulletDuration, angle);
    }
}

void EnemySystem::tick()
{
    using namespace Engine::Components;

    trySpawnEnemies();
    tryChangeEnemiesMovement();
    tryMakeEnemyAttack();
}

bool EnemySystem::shouldSpawnEnemy()
{
    if (_clock.getElapsedTime().asMilliseconds() < rand() % 1000 + ENEMY_SPAWN_RATE) return false;
    _clock.restart();
    return rand() % 100 >= 25;
}

size_t EnemySystem::spawnEnemy(float posx, float posy)
{
    using namespace Engine::Components;

    EnemyData::EnemyType type       = getRandomEnemyType();
    auto                 attributes = EnemyData::enemyTypeAttributes.at(type);

    size_t entityId =
        WORLD.createEntity(new PositionComponent(static_cast<int>(posx), static_cast<int>(posy)),
                           new RenderableComponent(attributes.spritePath, 20, 20, 0), new EnemyComponent(type),
                           new CollisionComponent(0, 0, 100, 100), new TypeComponent(TypeComponent::enemy));
    WORLD.getMutEntity(entityId).addComponent<MovingComponent>(new MovingComponent(
        sf::Vector2f{static_cast<float>(WORLD.getEntity(entityId).getComponent<PositionComponent>()->x),
                     static_cast<float>(WORLD.getEntity(entityId).getComponent<PositionComponent>()->y)},
        3000, {-100, -100}));
    return entityId;
}

EnemyData::EnemyType EnemySystem::getRandomEnemyType()
{
    int chance = rand() % 100;
    if (chance < 70)
        return EnemyData::EnemyType::Weak;
    else if (chance < 95)
        return EnemyData::EnemyType::Medium;
    else
        return EnemyData::EnemyType::Strong;
}
