/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ExcludeCollision.component.hpp
*/

#include "R-Type/GameWorld/EnemyMakers.hpp"

std::map<size_t, std::function<size_t(float, bool)>> functionMap = {
    {0, EnemyMakers::basicEnemyMaker},
    {1, EnemyMakers::mediumEnemyMaker},
};

size_t EnemyMakers::basicEnemyMaker(float y, bool isAttacking)
{
    using namespace Engine::Components;
    using namespace Rtype::Components;

    ECS::World &world       = Engine::EngineClass::getEngine().world();
    auto        attributes  = EnemyData::enemyTypeAttributes.at(EnemyData::EnemyType::Weak);
    size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();

    ECS::id_t enemyId = world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                                           new RenderableComponent(attributes.spritePath, 20, 20, 0, 270),
                                           new EnemyComponent(attributes.health, EnemyData::EnemyType::Weak),
                                           new CollisionComponent(21, 23, 22, 22), new ExcludeCollisionComponent(0),
                                           new HealthComponent(20));

    ECS::Entity &enemy = world.getMutEntity(enemyId);
    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

    enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
        {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
    return enemyId;
}

size_t EnemyMakers::mediumEnemyMaker(float y, bool isAttacking)
{
    using namespace Engine::Components;

    ECS::World &world       = Engine::EngineClass::getEngine().world();
    auto        attributes  = EnemyData::enemyTypeAttributes.at(EnemyData::EnemyType::Medium);
    size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
    ECS::id_t   enemyId = world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                                             new RenderableComponent(attributes.spritePath, 20, 20, 0, 270),
                                             new EnemyComponent(attributes.health, EnemyData::EnemyType::Medium),
                                             new CollisionComponent(21, 23, 22, 22), new ExcludeCollisionComponent(0));

    ECS::Entity &enemy = world.getMutEntity(enemyId);

    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

    enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
        {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
    return enemyId;
}
