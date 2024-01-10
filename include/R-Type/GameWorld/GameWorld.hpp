// GameWorld.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "Entities.hpp"
#include "Subscribers.hpp"
#include "Systems.hpp"

namespace GameWorld
{
    inline ECS::World *createGameWorld()
    {
        auto world = new ECS::World();

        // Setup view and create entities
        Entities::createViewEntity(world);
        Entities::createParallax(world);
        // Entities::createPlayerEntities(world);
        // Entities::createEnemyQueue(world);
        // Entities::createWorldMoveProgress(world);
        Entities::createOptionsEntities(world);
        // Entities::createChangeSceneButton(world, "./assets/menu/button_normal/normal_off.png", "menu", {150, 150},
        //                                   {2, 2}, 4);
        // Entities::createEnemyQueue(world);
        // Entities::createWorldMoveProgress(world);

        // Add systems
        Systems::addPhysics(world);
        Systems::addPlayerMovement(world);
        Systems::addEnemySystem(world);
        Systems::addParallaxSystem(world);
        Systems::addBulletSystem(world);
        Systems::addWorldMoveSystem(world);
        Systems::addAnimationSystem(world);
        Systems::addDeathAnimationSystem(world);
        Systems::addHealthSystem(world);

        // Subscribe to events
        Subscribers::subscribeToEvents(world);

        return world;
    }

    inline void addToGameWorldServerSide(ECS::World *world, int players)
    {
        // Setup view and create entities
        for (int i = 0; i < players; i++)
            Entities::createPlayerEntities(world, i);
        // Entities::createEnemyQueue(world);
        Entities::createWorldMoveProgress(world);
    }

    // inline std::shared_ptr<ECS::World> createMenuWorld(Engine::EngineClass &engine)
    inline ECS::World *createMenuWorld()
    {
        auto world = new ECS::World();

        Entities::createViewEntity(world);
        Entities::createButtonEntities(world);
        Entities::createOptionsEntities(world);
        Entities::createParallax(world);
        Systems::addUISystem(world);

        Systems::addParallaxSystem(world);

        // Disclaimer: this hasn't been done by me, but trying to make it pretty it crashes, as I think when we switch
        // world while being in one doing a function, it crashes, so we should keep a shared_ptr of the world
        // while we're in it, and remove it safely when we've truly exited the world
        // engine.addWorldFactory("menu", [world]() { return world; });

        return world;
    }
} // namespace GameWorld
