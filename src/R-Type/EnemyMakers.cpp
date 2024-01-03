#include "R-Type/GameWorld/EnemyMakers.hpp"

std::map<size_t, std::function<size_t(float, bool)>> functionMap = {
    {0, EnemyMakers::basicEnemyMaker} // et ainsi de suite pour d'autres fonctions
};

size_t EnemyMakers::basicEnemyMaker(float y, bool isAttacking)
{
    using namespace Engine::Components;
    ECS::World  &world       = Engine::EngineClass::getEngine().world();
    auto         attributes  = EnemyData::enemyTypeAttributes.at(EnemyData::EnemyType::Weak);
    size_t       windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
    id_t         enemyId = world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                                              new RenderableComponent(attributes.spritePath, 20, 20, 0),
                                              new EnemyComponent(attributes.health, EnemyData::EnemyType::Weak),
                                              new CollisionComponent(21, 23, 22, 22), new ExcludeCollisionComponent(0));
    ECS::Entity &enemy   = world.getMutEntity(enemyId);
    if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));
    enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
        {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
    return enemyId;
}
