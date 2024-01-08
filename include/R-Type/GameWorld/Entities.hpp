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
#include "Engine/Components/View.component.hpp"
#include "Engine/Components/WorldMoveProgress.component.hpp"
#include "R-Type/Components/Enemy.component.hpp"
#include "R-Type/Components/EnemyAttack.component.hpp"
#include "R-Type/Components/EnemyMovements.component.hpp"
#include "R-Type/Components/EnemyQueue.component.hpp"
#include "R-Type/Components/Player.component.hpp"
#include "R-Type/GameWorld/EnemyMakers.hpp"

namespace Entities
{
    inline void createViewEntity(ECS::World *world)
    {
        ECS::id_t ship_id = world->createEntity(new Engine::Components::ViewComponent());

        auto &entity = world->getMutEntity(ship_id);
        for (auto &it : entity.getComponents())
            it.second->setHasChanged(false);
    }

    inline void createPlayerEntities(ECS::World *world)
    {
        using namespace Engine::Components;

        [[maybe_unused]] ECS::id_t ship_id =
            world->createEntity(new PlayerComponent(), new PositionComponent(100, 100),
                                new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 90),
                                new CollisionComponent(9, 11, 30, 26), new SpeedComponent(150));
    }

    inline void createButtonEntities(ECS::World *world)
    {
        using namespace Engine::Components;

        [[maybe_unused]] auto startButtonEntity = world->createEntity(
            new ButtonComponent("Start Game", []() { std::cout << "Start Game" << std::endl; }),
            new PositionComponent(100, 100),
            new RenderableComponent("./assets/MainShip/MainShip-Base-Fullhealth.png", 0, 0, 1, 0, {1, 1}, true));

        world->createEntity(new ButtonComponent("Start Waiting Room",
                                                []() {
                                                    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
                                                    engine.network().startServer(5555);
                                                }),
                            new PositionComponent(200, 200),
                            new RenderableComponent("./assets/logo.png", 0, 0, 1, 0, {1, 1}, true));

        world->createEntity(new ButtonComponent("Join Waiting Room",
                                                []() {
                                                    Engine::EngineClass &engine = Engine::EngineClass::getEngine();
                                                    engine.network().connectToServer("localhost", 5555);
                                                }),
                            new PositionComponent(400, 200),
                            new RenderableComponent("./assets/logo.png", 0, 0, 1, 0, {1, 1}, true));
    }

    inline void createBackground(ECS::World *world, const std::string &texturePath, ParallaxLayer layer, float speed,
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
            ECS::id_t ship_id =
                world->createEntity(new PositionComponent(0, 0), renderable, new ParallaxComponent(layer, speed));
            auto &entity = world->getMutEntity(ship_id);
            for (auto &it : entity.getComponents())
                it.second->setHasChanged(false);
        } else {
            renderable->position = {trueSize.x, 0};
            ECS::id_t ship_id    = world->createEntity(new PositionComponent(trueSize.x, 0), renderable,
                                                       new ParallaxComponent(layer, speed));
            auto     &entity     = world->getMutEntity(ship_id);
            for (auto &it : entity.getComponents())
                it.second->setHasChanged(false);
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

    inline void createEnemyQueue(ECS::World *world)
    {
        using namespace Engine::Components;

        auto test = world->createEntity(
            new EnemyQueueComponent({std::make_pair(false, std::make_pair(std::make_tuple(100, 50, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(150, 60, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(200, 70, true), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(250, 80, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(300, 90, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(350, 100, false), 0)),
                                     std::make_pair(false, std::make_pair(std::make_tuple(400, 110, true), 0))}));
    }

    inline void createWorldMoveProgress(ECS::World *world)
    {
        using namespace Engine::Components;

        auto   now         = std::chrono::high_resolution_clock::now();
        auto   epoch       = now.time_since_epoch();
        size_t currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(epoch).count();

        world->createEntity(new WorldMoveProgressComponent(currentTime, 0, 50));
    }
} // namespace Entities
