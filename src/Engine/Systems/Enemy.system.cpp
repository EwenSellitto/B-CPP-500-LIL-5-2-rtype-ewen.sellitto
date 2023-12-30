/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Animation.system.cpp
*/

#include "Engine/Systems/Enemy.system.hpp"

#include "ECS/World.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/Enemy.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Engine.hpp"

using namespace Engine::System;

void EnemySystem::configure([[maybe_unused]] ECS::World &world)
{
}

void EnemySystem::unconfigure()
{
}

void EnemySystem::tick()
{
    using namespace Engine::Components;
    ECS::World                &world    = getWorld();
    std::vector<ECS::Entity *> entities = world.getEntitiesWithComponents<RenderableComponent, EnemyComponent>();

    // if (shouldSpawnEnemy()) spawnEnemy();
}

bool EnemySystem::shouldSpawnEnemy()
{
    if (_clock.getElapsedTime().asMilliseconds() < rand() % 1000 + ENEMY_SPAWN_RATE) return false;
    _clock.restart();
    return rand() % 100 >= 25;
}

void EnemySystem::spawnEnemy(float posx, float posy)
{
    using namespace Engine::Components;

    EnemyData::EnemyType type       = getRandomEnemyType();
    auto      attributes = EnemyData::enemyTypeAttributes.at(type);

    getWorld().createEntity(new PositionComponent(static_cast<int>(posx), static_cast<int>(posy)),
                            new RenderableComponent(attributes.spritePath, 20, 20, 0),
                            new EnemyComponent(attributes.health, type), new CollisionComponent(0, 0, 100, 100),
                            new TypeComponent(TypeComponent::enemy));
}

EnemyData::EnemyType EnemySystem::getRandomEnemyType()
{
    int chance = rand() % 100;
    if (chance < 70)
        return EnemyData::EnemyType::Weak;
    else if (chance < 95)
        return EnemyData::EnemyType::Normal;
    else
        return EnemyData::EnemyType::Strong;
}
