/*
** EPITECH PROJECT, 2023
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** ExcludeCollision.component.hpp
*/

#include "R-Type/GameWorld/EnemyMakers.hpp"

std::map<size_t, std::function<size_t(float, bool, std::vector<std::pair<size_t, sf::Vector2f>>)>> functionMap = {
    {0, EnemyMakers::basicEnemyMaker},
    {1, EnemyMakers::mediumEnemyMaker},
    {2, EnemyMakers::strongEnemyMaker},
    {3, EnemyMakers::ObstacleMaker},
};

size_t EnemyMakers::basicEnemyMaker(float y, bool isAttacking,
                                    std::vector<std::pair<size_t, sf::Vector2f>> PatternMovements)
{
    using namespace Engine::Components;
    using namespace Rtype::Components;

    ECS::World &world       = Engine::EngineClass::getEngine().world();
    size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
    ECS::id_t   enemyId =
        world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                           new RenderableComponent("Klaed-Scout-Base"), new EnemyComponent(EnemyData::EnemyType::Weak),
                           new Rtype::Components::HealthComponent(20), new CollisionComponent("Klaed-Scout-Base"),
                           new ExcludeCollisionComponent(0));

    ECS::Entity &enemy = world.getMutEntity(enemyId);

    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

    enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
        // {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
        PatternMovements));

    return enemyId;
}

size_t EnemyMakers::mediumEnemyMaker(float y, bool isAttacking,
                                     std::vector<std::pair<size_t, sf::Vector2f>> PatternMovements)
{
    using namespace Engine::Components;
    using namespace Rtype::Components;

    ECS::World &world       = Engine::EngineClass::getEngine().world();
    size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
    ECS::id_t   enemyId     = world.createEntity(
        new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
        new RenderableComponent("Klaed-Battlecruiser-Base"), new EnemyComponent(EnemyData::EnemyType::Medium),
        new Rtype::Components::HealthComponent(120), new CollisionComponent("Klaed-Battlecruiser-Base"),
        new ExcludeCollisionComponent(0));

    ECS::Entity &enemy = world.getMutEntity(enemyId);

    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

    if (static_cast<float>(enemy.getComponent<PositionComponent>()->x) > 800) {
        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
    } else {
        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            // {std::make_pair(800, sf::Vector2f(-50, 50)), std::make_pair(800, sf::Vector2f(-50, -50))}
            PatternMovements));
    }
    return enemyId;
}

size_t EnemyMakers::strongEnemyMaker(float y, bool isAttacking,
                                     std::vector<std::pair<size_t, sf::Vector2f>> PatternMovements)
{
    using namespace Engine::Components;
    using namespace Rtype::Components;

    ECS::World &world       = Engine::EngineClass::getEngine().world();
    size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
    ECS::id_t   enemyId     = world.createEntity(
        new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
        new RenderableComponent("Klaed-Dreadnought-Base"), new EnemyComponent(EnemyData::EnemyType::Strong),
        new Rtype::Components::HealthComponent(700), new CollisionComponent("Klaed-Dreadnought-Base"),
        new ExcludeCollisionComponent(0));

    ECS::Entity &enemy = world.getMutEntity(enemyId);

    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

    if (static_cast<float>(enemy.getComponent<PositionComponent>()->x) > 800) {
        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
    } else {
        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            // {std::make_pair(800, sf::Vector2f(-50, 50)), std::make_pair(800, sf::Vector2f(-50, -50))}
            PatternMovements));
    }
    return enemyId;
}

size_t EnemyMakers::ObstacleMaker(float y, bool isAttacking,
                                  std::vector<std::pair<size_t, sf::Vector2f>> PatternMovements)
{
    using namespace Engine::Components;
    using namespace Rtype::Components;

    ECS::World &world       = Engine::EngineClass::getEngine().world();
    size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
    ECS::id_t   enemyId =
        world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                           new RenderableComponent("Asteroid01-Base"), new EnemyComponent(EnemyData::EnemyType::Weak),
                           new Rtype::Components::HealthComponent(10000000), new CollisionComponent("Asteroid01-Base"),
                           new ExcludeCollisionComponent(0));

    ECS::Entity &enemy = world.getMutEntity(enemyId);

    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

    enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
        // {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
        PatternMovements));

    return enemyId;
}
