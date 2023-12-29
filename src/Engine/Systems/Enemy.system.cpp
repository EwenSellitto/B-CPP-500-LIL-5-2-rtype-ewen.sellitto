/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/Enemy.system.hpp"

#include "ECS/World.hpp"
#include "Engine/Components/Enemy.component.hpp"
#include "Engine/Components/Position.compnent.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void EnemySystem::configure([[maybe_unused]] ECS::World &world)
{
    return;
}

void EnemySystem::unconfigure()
{
    return;
}

void EnemySystem::tick()
{
    using namespace Engine::Components;
    ECS::World                &world    = getWorld();
    std::vector<ECS::Entity *> entities = world.getEntitiesWithComponents<RenderableComponent,
                                                                          EnemyComponent>();

    if (shouldSpawnEnemy()) spawnEnemy();
}

bool EnemySystem::shouldSpawnEnemy()
{
    return rand() % 100 >= 25;
}

void EnemySystem::spawnEnemy() {
    using namespace Engine::Components;

    EnemyType type = getRandomEnemyType();
    auto attributes = enemyTypeAttributes.at(type);

    getWorld().createEntity(new PositionComponent(rand() % 800, rand() % 600),
                            new RenderableComponent(attributes.spritePath, 20, 20, 0),
                            new EnemyComponent(attributes.health, type));
}

EnemyType EnemySystem::getRandomEnemyType() {
    int chance = rand() % 100;
    if (chance < 70) return EnemyType::Weak;
    else if (chance < 95) return EnemyType::Normal;
    else return EnemyType::Strong;
}