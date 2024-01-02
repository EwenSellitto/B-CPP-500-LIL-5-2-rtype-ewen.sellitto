// Entities.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Components/Button.component.hpp"
#include "Engine/Components/Collision.component.hpp"
#include "Engine/Components/ExcludeCollision.component.hpp"
#include "Engine/Components/Parallax.component.hpp"
#include "Engine/Components/Position.component.hpp"
#include "Engine/Components/Renderable.component.hpp"
#include "Engine/Components/Speed.component.hpp"
#include "Engine/Components/Type.component.hpp"
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Player.component.hpp"

namespace Entities
{
    inline void createViewEntity(ECS::World *world)
    {
        world->createEntity(new Engine::Components::ViewComponent());
    }

    inline void createPlayerEntities(ECS::World *world)
    {
        using namespace Engine::Components;

        id_t ship_id = world->createEntity(
            new PlayerComponent(), new PositionComponent(100, 100),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 0),
            new CollisionComponent(9, 11, 30, 26), new TypeComponent(TypeComponent::player), new SpeedComponent(150));
    }

    void createButtonEntities(ECS::World *world)
    {
        using namespace Engine::Components;

        auto startButtonEntity = world->createEntity(
            new ButtonComponent("Start Game", []() { std::cout << "Start Game" << std::endl; }),
            new PositionComponent(100, 100),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 0, {1, 1}, true));
    }

    void createBackground(ECS::World *world, const std::string &texturePath, ParallaxLayer layer, float speed,
                          bool first, int priority)
    {

        using namespace Engine::Components;
        sf::Vector2f windowSize = {0, 0};

        world->each<ViewComponent>(
            [&windowSize]([[maybe_unused]] ECS::Entity *entity, ECS::ComponentHandle<ViewComponent> viewComp) {
                windowSize = viewComp->view.getSize();
            });

        auto  renderable = new RenderableComponent(texturePath, {0, 0}, priority);
        float scaleRatio = windowSize.y / renderable->texture.getSize().y;

        renderable->scale           = {scaleRatio, scaleRatio};
        sf::Vector2<float> trueSize = {static_cast<float>(renderable->size.x * scaleRatio),
                                       static_cast<float>(renderable->size.y * scaleRatio)};
        if (first) {
            renderable->position = {0, 0};
            world->createEntity(new PositionComponent(0, 0), renderable, new ParallaxComponent(layer, speed));
        } else {
            renderable->position = {trueSize.x, 0};
            world->createEntity(new PositionComponent(trueSize.x, 0), renderable, new ParallaxComponent(layer, speed));
        }
    }

    inline void createParallax(ECS::World *world)
    {
        createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png",
                         ParallaxLayer::FarBackground, 1, true, -5);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer01-Void.png",
                         ParallaxLayer::FarBackground, 1, false, -5);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png",
                         ParallaxLayer::MidBackground, 2, true, -4);
        createBackground(world, "./assets/Environnement/Starrybackground-Layer02-Stars.png",
                         ParallaxLayer::MidBackground, 2, false, -4);
        createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                         ParallaxLayer::NearBackground, 4, true, -3);
        createBackground(world, "./assets/Environnement/Starrybackground-LayerX-BigStar2.png",
                         ParallaxLayer::NearBackground, 4, false, -3);
    }

    size_t basicEnemyMaker(float y, bool isAttacking)
    {
        using namespace Engine::Components;

        ECS::World &world       = Engine::EngineClass::getEngine().world();
        auto        attributes  = EnemyData::enemyTypeAttributes.at(EnemyData::EnemyType::Weak);
        size_t      windowSizeX = Engine::EngineClass::getEngine().getWindowSizeX();
        id_t enemyId = world.createEntity(new PositionComponent(static_cast<int>(windowSizeX), static_cast<int>(y)),
                                          new RenderableComponent(attributes.spritePath, 20, 20, 0),
                                          new EnemyComponent(attributes.health, EnemyData::EnemyType::Weak),
                                          new CollisionComponent(21, 23, 22, 22), new ExcludeCollisionComponent(0));

        ECS::Entity &enemy = world.getMutEntity(enemyId);

        if (isAttacking) enemy.addComponent(new EnemyAttackComponent(2000, 0, {-150 * 3, 500 * 3}, 400 * 3));

        enemy.addComponent<EnemyMovementsComponent>(new EnemyMovementsComponent(
            {std::make_pair(800, sf::Vector2f(-100, 100)), std::make_pair(800, sf::Vector2f(-100, -100))}));
        return enemyId;
    }

    inline void createEnemyQueue(ECS::World *world)
    {
        using namespace Engine::Components;

        world->createEntity(new EnemyQueueComponent(
            {std::make_pair(false, std::make_pair(std::make_tuple(100, 50, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(150, 60, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(200, 70, true), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(250, 80, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(300, 90, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(350, 100, false), basicEnemyMaker)),
             std::make_pair(false, std::make_pair(std::make_tuple(400, 110, true), basicEnemyMaker))}));
    }

    inline void createWorldMoveProgress(ECS::World *world)
    {
        using namespace Engine::Components;

        using namespace Engine::Components;

        auto   now         = std::chrono::high_resolution_clock::now();
        auto   epoch       = now.time_since_epoch();
        size_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        world->createEntity(new WorldMoveProgressComponent(currentTime, 0, 50));
    }
} // namespace Entities
