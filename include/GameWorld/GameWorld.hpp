// GameWorld.hpp
#pragma once
#include "ECS/World.hpp"
#include "Engine/Engine.hpp"
#include "GameWorld/Entities.hpp"
#include "GameWorld/Subscribers.hpp"
#include "GameWorld/Systems.hpp"

namespace GameWorld
{
    std::shared_ptr<ECS::World> createGameWorld()
    {
        auto world = std::make_shared<ECS::World>();

        // Setup view and create entities
        Entities::createViewEntity(world);
        Entities::createParallax(world);
        Entities::createPlayerEntities(world);
        Entities::createEnemyQueue(world);
        Entities::createWorldMoveProgress(world);

        // Add systems
        Systems::addPhysics(world);
        Systems::addPlayerMovement(world);
        Systems::addEnemySystem(world);
        Systems::addParallaxSystem(world);
        Systems::addBulletSystem(world);
        Systems::addWorldMoveSystem(world);
        Systems::addAnimationSystem(world);
        Systems::addRenderer(world);

        // Subscribe to events
        Subscribers::subscribeToEvents(world);

        return world;
    }

    std::shared_ptr<ECS::World> createMenuWorld(Engine::EngineClass &engine) {
        auto world = std::make_shared<ECS::World>();

        Entities::createViewEntity(world);
        Entities::createButtonEntities(world);

        Systems::addRenderer(world);
        Systems::addUISystem(world);

        engine.setStartWorld("menu");
        // Disclaimer: this hasn't been done by me, but trying to make it pretty it crashes, as I think when we switch
        // world while being in one doing a function, it crashes, so we should keep a shared_ptr of the world
        // while we're in it, and remove it safely when we've truly exited the world
        engine.addWorldFactory("menu", [world]() { return world; });

        return world;
    }
} // namespace GameWorld
