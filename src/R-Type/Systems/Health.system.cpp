/*
** EPITECH PROJECT, 2024
** B-CPP-500-LIL-5-2-rtype-ewen.sellitto
** File description:
** Health.system.cpp
*/

#include "R-Type/Systems/Health.system.hpp"

#include "Engine/Components/Animation.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "R-Type/Components/DeathAnimation.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/Health.component.hpp"

using namespace Rtype::Systems;

static void enemyDeath(ECS::Entity *entity)
{
    using namespace Engine::Components;

    entity->removeComponent<AnimationComponent>();
    entity->removeComponent<CollisionComponent>();
    entity->removeComponent<EnemyAttackComponent>();
    auto enemyComponent = entity->getComponent<EnemyComponent>();

    switch (enemyComponent->enemyType) {
        case EnemyData::EnemyType::Weak:
            entity->addComponent(new DeathAnimationComponent("./assets/klaed/Klaed-Fighter-Destruction.png", 0, 0, 64,
                                                             64, 64, 64, 100, 9));
            break;
        case EnemyData::EnemyType::Normal:
        case EnemyData::EnemyType::Strong:
            entity->removeAllComponents();
    }
}

void HealthSystem::tick()
{
    using namespace Engine::Components;

    auto entities = WORLD.getEntitiesWithComponents<Components::HealthComponent>();

    for (const auto &entity : entities) {
        auto health = entity->getComponent<Components::HealthComponent>();

        if (health->health > 0) continue;

        if (entity->has<Engine::Components::EnemyComponent>()) {
            enemyDeath(entity);
        } else {
            entity->removeAllComponents();
        }
    }
}
